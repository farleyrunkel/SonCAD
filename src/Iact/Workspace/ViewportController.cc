// Copyright [2024] SunCAD

#include "Iact/Workspace/ViewportController.h"

#include <Graphic3d_Vec4.hxx>
#include <Standard_NotImplemented.hxx>

#include "Core/Project/VisualStyles.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/ViewportParameterSet.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Occt/OcctHelper/AisHelper.h"

ViewportController::ViewportController(const Handle(Viewport)& viewport,
									   const Handle(WorkspaceController)& wc)
{
	_Viewport = viewport;
	_WorkspaceController = wc;
	Init();
}

Handle(Viewport) ViewportController::GetViewport()
{
	return _Viewport;
}

Handle(WorkspaceController) ViewportController::GetWorkspaceController()
{
	return _WorkspaceController;
}

bool ViewportController::LockedToPlane() const
{
	return _LockedToPlane;
}

void ViewportController::SetLockedToPlane(bool value)
{
	if(_LockedToPlane == value)
		return;

	if(value)
	{
		SetPredefinedView(PredefinedViews::WorkingPlane);
	}

	_LockedToPlane = value;
	_SetViewCube(!_LockedToPlane);
	_SetTrihedron(!_LockedToPlane);
	RaisePropertyChanged("LockedToPlane");
}

void ViewportController::InitWindow()
{
	if(_ZoomFitAllOnInit)
	{
		_ZoomFitAllOnInit = false;
		ZoomFitAll();
	}
	_Viewport->GetV3dView()->Update();
	_Viewport->GetV3dView()->MustBeResized();
	_Viewport->GetV3dView()->SetImmediateUpdate(false);

	_UpdateParameter();
}

void ViewportController::Init()
{
	ViewportParameterSet::ParameterChanged.connect(std::bind(&ViewportController::_ViewportParameterSet_ParameterChanged, this,
												   std::placeholders::_1,
												   std::placeholders::_2));

	auto parameterSet = InteractiveContext::Current()->GetParameterSets()->Get<ViewportParameterSet>();

	_Viewport->Init(parameterSet->EnableAntialiasing());
}

void ViewportController::_UpdateParameter()
{
	auto parameterSet = InteractiveContext::Current()->GetParameterSets()->Get<ViewportParameterSet>();
	_SetViewCube(parameterSet->ShowViewCube(), parameterSet->ViewCubeSize(), parameterSet->ViewCubeAnimationDuration());
	_SetTrihedron(parameterSet->ShowTrihedron());
	_ShowTrihedron = parameterSet->ShowTrihedron();
}

void ViewportController::_ViewportParameterSet_ParameterChanged(OverridableParameterSet* set, std::string key)
{
	_UpdateParameter();
}

void ViewportController::_SetMouseMoveMode(MouseMoveMode mode)
{
	switch(mode)
	{
	case MouseMoveMode::Panning:
		_CurrentMouseMoveMode = MouseMoveMode::Panning;
		break;

	case MouseMoveMode::Rotating:
		_CurrentMouseMoveMode = MouseMoveMode::Rotating;
		_GravityPoint = _Viewport->GetV3dView()->GravityPoint();
		break;

	case MouseMoveMode::Twisting:
		_CurrentMouseMoveMode = MouseMoveMode::Twisting;
		break;

	case MouseMoveMode::Zooming:
		_Viewport->GetV3dView()->StartZoomAtPoint(_StartedMousePosition.x(), _StartedMousePosition.y());
		_CurrentMouseMoveMode = MouseMoveMode::Zooming;
		break;
	}
}

void ViewportController::_ResetMouseMoveMode()
{
	_GravityPoint = gp_Pnt(0, 0, 0);
	_CurrentMouseMoveMode = MouseMoveMode::None;
}

void ViewportController::Rotate(double yawDeg, double pitchDeg, double rollDeg)
{
	if(!_LockedToPlane) // 仅当未锁定到平面时执行旋转
	{
		Handle(V3d_View) view = _Viewport->GetV3dView();
		if(!view) return;

		// 定义常量：限制俯仰角度（接近 90 度）
		const double orbitProjectionConstraint = M_PI / 2.0 - 0.000000000001;

		// 处理俯仰和偏航
		if(std::abs(yawDeg) > 0.001 || std::abs(pitchDeg) > 0.001)
		{
			// 检查并重置 Twist（假设 Viewport 有 Twist 属性或方法）
			// 如果你的 Viewport 没有 Twist，注释掉这部分
			// 示例：if (_Viewport->Twist() == 180.0) _Viewport->SetTwist(0.0);

			// 转换为弧度
			double pitch = pitchDeg * M_PI / 180.0;
			double yaw = yawDeg * M_PI / 180.0;

			// 获取方向
			gp_Dir upDir = _Viewport->GetUpDirection();
			gp_Dir viewDir = _Viewport->GetViewDirection();

			// 计算剩余角度，限制俯仰
			gp_Ax2 xoy(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)); // XOY 平面
			double angleLeft = orbitProjectionConstraint - xoy.Angle(gp_Ax2(gp_Pnt(0, 0, 0), upDir));
			if(viewDir.Z() < 0 && pitch < -angleLeft)
			{
				pitch = -angleLeft;
			}
			else if(viewDir.Z() > 0 && pitch > angleLeft)
			{
				pitch = angleLeft;
			}

			// 获取重心点
			gp_Pnt gravityPoint = _GravityPoint.IsEqual(gp_Pnt(0, 0, 0), 0.001) ? view->GravityPoint() : _GravityPoint;

			// 应用俯仰变换（绕右方向）
			gp_Trsf trsf1;
			trsf1.SetRotation(gp_Ax1(gravityPoint, _Viewport->GetRightDirection()), pitch);
			view->Camera()->Transform(trsf1);

			// 应用偏航变换（绕 Z 轴）
			gp_Trsf trsf2;
			trsf2.SetRotation(gp_Ax1(gravityPoint, gp_Dir(0, 0, 1)), yaw);
			view->Camera()->Transform(trsf2);
		}

		// 处理滚转
		if(std::abs(rollDeg) > 0.001)
		{
			view->Turn(V3d_Z, rollDeg * M_PI / 180.0, Standard_True);
		}
	}

	// 更新视图
	_Viewport->GetV3dView()->Update();
	_WorkspaceController->Invalidate();
	_Viewport->OnViewMoved();
}

void ViewportController::Pan(double dx, double dy)
{
	_Viewport->GetV3dView()->Panning(dx, dy);
	_WorkspaceController->Invalidate();
	_Viewport->OnViewMoved();
}

void ViewportController::Zoom(const Graphic3d_Vec2d& pos, double value)
{
	double delta = value * 20.0;
	if(_CurrentMouseMoveMode != MouseMoveMode::Zooming)
	{
		_Viewport->GetV3dView()->StartZoomAtPoint(pos.x(), pos.y());
	}

	_Viewport->GetV3dView()->ZoomAtPoint(pos.x(), pos.y() - delta, pos.x(), pos.y() + delta);
	_WorkspaceController->Invalidate();
	_Viewport->OnViewMoved();
}

void ViewportController::Zoom(double value)
{
	if(value > 0)
	{
		_Viewport->GetV3dView()->SetZoom(1.0 + value, true);
	}
	else if(value < 0)
	{
		_Viewport->GetV3dView()->SetZoom(1.0 / (1.0 - value), true);
	}
	_Viewport->GetV3dView()->Redraw();
	_Viewport->OnViewMoved();
}

void ViewportController::ZoomFitAll()
{
	_Viewport->GetV3dView()->FitAll(0.1, false);
	_Viewport->GetV3dView()->ZFitAll(1.0);
	_Viewport->OnViewMoved();
}

void ViewportController::ZoomFitSelected()
{
	throw Standard_NotImplemented(
		"ViewportController::ZoomFitSelected() - method is not implemented");
}

bool ViewportController::IsInRubberbandSelection() const
{
	return !_AisRubberBand.IsNull();
}

void ViewportController::StartRubberbandSelection(RubberbandSelectionMode mode, 
												  bool includeTouched, 
												  const Graphic3d_Vec2d& position)
{
	throw Standard_NotImplemented(
		"ViewportController::StartRubberbandSelection(RubberbandSelectionMode mode, "
		"bool includeTouched,"
		"const Graphic3d_Vec2d & position) - method is not implemented");
}

void ViewportController::_SetTrihedron(bool visible)
{
	if(visible)
	{
		_Viewport->GetV3dView()->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_BLACK, 0.1, V3d_ZBUFFER);
	}
	else
	{
		_Viewport->GetV3dView()->TriedronErase();
	}
}

void ViewportController::MouseMove(const Graphic3d_Vec2d& pos, Aspect_VKeyFlags keys, MouseMoveMode mode)
{
	if(IsInRubberbandSelection())
	{
		_LastMousePosition = pos;
		_UpdateRubberbandSelection();
		_WorkspaceController->Invalidate(true);
		return;
	}

	if(_CurrentMouseMoveMode != mode)
	{
		if(mode == MouseMoveMode::None)
		{
			_ResetMouseMoveMode();
		}
		else
		{
			_StartedMousePosition = pos;
			_SetMouseMoveMode(mode);
		}
	}

	switch(_CurrentMouseMoveMode)
	{
	case MouseMoveMode::Panning:
		_Viewport->GetV3dView()->Pan(pos.x() - _LastMousePosition.x(), _LastMousePosition.y() - pos.y());
		_Viewport->OnViewMoved();
		break;

	case MouseMoveMode::Twisting:
		Rotate(0, 0, (pos.y() - _LastMousePosition.y()) / 12.0);
		break;

	case MouseMoveMode::Rotating:
		Rotate((_LastMousePosition.x() - pos.x()) / 6.0, (_LastMousePosition.y() - pos.y()) / 6.0, 0);
		break;

	case MouseMoveMode::Zooming:
		_Viewport->GetV3dView()->ZoomAtPoint((int)_LastMousePosition.x(), (int)pos.y(), (int)pos.x(), (int)_LastMousePosition.y());
		_Viewport->OnViewMoved();
		break;
	}

	_WorkspaceController->MouseMove(this, pos, keys);
	_WorkspaceController->Invalidate();
	_LastMousePosition = pos;
}

void ViewportController::MouseMove(Aspect_VKeyFlags keys)
{
	if(!_AisRubberBand.IsNull())
	{
		return;
	}
	_WorkspaceController->MouseDown(this, keys);
}

void ViewportController::MouseDown(Aspect_VKeyFlags keys)
{
	_WorkspaceController->MouseDown(this, keys);
}

void ViewportController::MouseUp(Aspect_VKeyFlags keys)
{
	if(IsInRubberbandSelection())
	{
		_StopRubberbandSelection();
	}
	_WorkspaceController->MouseUp(this, keys);
}

void ViewportController::_StopRubberbandSelection()
{
	if(_AisRubberBand.IsNull()) return;

	_WorkspaceController->GetWorkspace()->AisContext()->Remove(_AisRubberBand, false);
	_AisRubberBand.Nullify();

	switch(_RubberbandMode)
	{
	case ViewportController::Rectangle:
		_WorkspaceController->SelectByRectangle(_CalcRectangleSelectionPoints(false), _RubberbandIncludeTouched, this);
		break;
	case ViewportController::Freehand:
		_RubberbandPoints.push_back(_RubberbandPoints[0]);
		_WorkspaceController->SelectByPolyline(_RubberbandPoints, _RubberbandIncludeTouched, this);
		break;
	default:
		break;
	}
	_RubberbandPoints.clear();
	_WorkspaceController->Invalidate(true);
}

void ViewportController::_SetViewCube(bool isVisible)
{
	auto aisContext = _Viewport->GetWorkspace()->AisContext();

	if(_ViewCube.IsNull())
		return;

	if(isVisible && !aisContext->IsDisplayed(_ViewCube))
	{
		aisContext->Display(_ViewCube, false);
		//_WorkspaceController->invalidate(true);
	}
	else if(!isVisible && aisContext->IsDisplayed(_ViewCube))
	{
		aisContext->Remove(_ViewCube, false);
		//_WorkspaceController->invalidate(true);
	}
}

void ViewportController::_SetViewCube(bool isVisible, int size, double duration)
{
	auto aisContext = _Viewport->GetWorkspace()->AisContext();

	// 如果视图立方体已存在，则使用现有方法更新其显示状态
	if(!_ViewCube.IsNull())
	{
		_SetViewCube(isVisible);
		return;
	}

	// 如果不需要显示视图立方体则直接返回
	if(!isVisible) return;

	// 加载位图资源
	//QImage bitmap = ResourceUtils::readBitmapFromResource("Visual/ViewCubeSides.png");
	//if (bitmap.isNull()) {
	//	qCritical() << "Could not load view cube texture from resource.";
	//    return;
	//}

	//// 将位图转换为 PixMap 格式
	//auto pixmap = PixMapHelper::convertFromBitmap(bitmap);
	//if (pixmap.IsNull()) {
	//	qCritical() << "Could not load view cube texture into pixmap.";
	//    return;
	//}

	// 初始化视图立方体
	_ViewCube = new AIS_ViewCube();
	_ViewCube->SetSize(size * _Viewport->DpiScale());
	_ViewCube->SetBoxFacetExtension(size * _Viewport->DpiScale() * 0.15);
	_ViewCube->SetViewAnimation(_Viewport->AisAnimationCamera());
	_ViewCube->SetFixedAnimationLoop(false);
	_ViewCube->SetDrawAxes(false);
	_ViewCube->SetDuration(duration);
	_ViewCube->SetResetCamera(true);
	_ViewCube->SetFitSelected(true);
	//_ViewCube->SetTexture(pixmap);

	// 设置位置及透视效果
	_ViewCube->SetTransformPersistence(new Graphic3d_TransformPers(
		Graphic3d_TMF_TriedronPers, Aspect_TOTP_RIGHT_UPPER, Graphic3d_Vec2i(100, 100)));

	// 配置颜色
	Quantity_Color sideColor, edgeColor, cornerColor;
	Quantity_Color::ColorFromHex("d9dfe5", sideColor);
	Quantity_Color::ColorFromHex("93a4b6", edgeColor);
	Quantity_Color::ColorFromHex("a6b4c3", cornerColor);

	_ViewCube->BoxSideStyle()->SetColor(sideColor);
	_ViewCube->BoxEdgeStyle()->SetColor(edgeColor);
	_ViewCube->BoxCornerStyle()->SetColor(cornerColor);

	// 设置材质
	auto material = new Graphic3d_MaterialAspect(Graphic3d_NOM_DEFAULT);
	material->SetAmbientColor(Quantity_Color(0.8, 0.8, 0.8, Quantity_TOC_sRGB));
	material->SetDiffuseColor(Quantity_Color(0.2, 0.2, 0.2, Quantity_TOC_sRGB));
	material->SetEmissiveColor(Quantity_NOC_BLACK);
	material->SetSpecularColor(Quantity_NOC_BLACK);
	_ViewCube->SetMaterial(*material);

	// 高亮属性
	auto highlightColor = Colors::Highlight;
	_ViewCube->DynamicHilightAttributes()->ShadingAspect()->SetColor(highlightColor);
	_ViewCube->DynamicHilightAttributes()->ShadingAspect()->SetMaterial(*material);

	// 显示或隐藏视图立方体
	if(isVisible)
	{
		aisContext->Display(_ViewCube, false);

		//for (const auto& viewport : _WorkspaceController->workspace()->viewports()) {
		//    aisContext->SetViewAffinity(_ViewCube, viewport->v3dView(), viewport.Get() == currentmyViewport.Get());
		//}
	}

	//_WorkspaceController->invalidate(true);
}

void ViewportController::_UpdateRubberbandSelection()
{
	if(_RubberbandMode == RubberbandSelectionMode::Rectangle)
	{
		auto points = _CalcRectangleSelectionPoints(true);
		_AisRubberBand->SetRectangle(points.x(), points.y(), points.z(), points.w());
	}

	else if(_RubberbandMode == RubberbandSelectionMode::Freehand)
	{
		int height = 0, width = 0;
		auto wind = _Viewport->GetV3dView()->Window();
		if(wind.IsNull()) return;
		wind->Size(width, height);

		int currentPointX = Max(0, Min((int)_LastMousePosition.x(), width));
		int currentPointY = Max(0, Min((int)_LastMousePosition.y(), height));
		auto lastPoint = _RubberbandPoints[_RubberbandPoints.size() - 2];
		auto distX = currentPointX - lastPoint.x();
		auto distY = currentPointY - lastPoint.y();
		if(distX * distX + distY * distY > RubberbandFreehandSelectionThresholdSquared)
		{
			_RubberbandPoints.push_back(Graphic3d_Vec2i(currentPointX, currentPointY));
		}
		else
		{
			_RubberbandPoints[_RubberbandPoints.size() - 1] = Graphic3d_Vec2i(currentPointX, currentPointY);
		}

		AisHelper::SetRubberbandPoints(_Viewport->GetV3dView()->Window(), _AisRubberBand, _RubberbandPoints);
	}

	_WorkspaceController->GetWorkspace()->AisContext()->Redisplay(_AisRubberBand, false);
}

Graphic3d_Vec4i ViewportController::_CalcRectangleSelectionPoints(bool bottomUp)
{
	int height = 0, width = 0;
	auto wind = _Viewport->GetV3dView()->Window();
	if(wind.IsNull()) return {};
	wind->Size(width, height);

	int left = Max(0, Min((int)_StartedMousePosition.x(), (int)_LastMousePosition.x()));
	int right = Min(width, Max((int)_StartedMousePosition.x(), (int)_LastMousePosition.x()));
	int top = Max(0, Min((int)_StartedMousePosition.y(), (int)_LastMousePosition.y()));
	int bottom = Min(height, Max((int)_StartedMousePosition.y(), (int)_LastMousePosition.y()));

	if(bottomUp)
	{
		top = height - top;
		bottom = height - bottom;
	}

	return Graphic3d_Vec4i(left, top, right, bottom);
}

void ViewportController::SetPredefinedView(PredefinedViews predefinedView)
{
	//if(predefinedView == PredefinedViews::WorkingPlane)
	//{
	//	const auto& plane = workspaceController()->workspace()->workingPlane();
	//	const auto& dir = plane.Axis().Direction();
	//	viewport()->view()->SetProj(dir.X(), dir.Y(), dir.Z());

	//	const auto& up = plane.YAxis().Direction();
	//	viewport()->view()->SetUp(up.X(), up.Y(), up.Z());
	//	return;
	//}

	//// 确保视图锁定或无视图立方体时无法进行旋转
	//if(m_lockedToPlane || !_ViewCube)
	//	return;

	V3d_TypeOfOrientation orientation;
	switch(predefinedView)
	{
	case PredefinedViews::Top:
		orientation = V3d_TypeOfOrientation_Zup_Top;
		break;
	case PredefinedViews::Bottom:
		orientation = V3d_TypeOfOrientation_Zup_Bottom;
		break;
	case PredefinedViews::Left:
		orientation = V3d_TypeOfOrientation_Zup_Left;
		break;
	case PredefinedViews::Right:
		orientation = V3d_TypeOfOrientation_Zup_Right;
		break;
	case PredefinedViews::Front:
		orientation = V3d_TypeOfOrientation_Zup_Front;
		break;
	case PredefinedViews::Back:
		orientation = V3d_TypeOfOrientation_Zup_Back;
		break;
	default:
		return;
	}

	Handle(AIS_ViewCubeOwner) viewCubeOwner = new AIS_ViewCubeOwner(_ViewCube, orientation);

	_ViewCube->HandleClick(viewCubeOwner);

	_Viewport->OnViewMoved();
}
