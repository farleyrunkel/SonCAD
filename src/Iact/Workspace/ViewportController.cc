// Copyright [2024] SunCAD

#include "Iact/Workspace/ViewportController.h"

#include "Iact/Workspace/WorkspaceController.h"
#include "Core/Project/VisualStyles.h"

ViewportController::ViewportController(const Handle(Viewport)& viewport, 
									   const Handle(WorkspaceController)& wc)
{
	myViewport = viewport;
	_WorkspaceController = wc;
	Init();
}

void ViewportController::SetViewCube(bool isVisible)
{
	auto aisContext = myViewport->GetWorkspace()->AisContext();

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

void ViewportController::SetViewCube(bool isVisible, int size, double duration)
{
	auto aisContext = myViewport->GetWorkspace()->AisContext();

	// 如果视图立方体已存在，则使用现有方法更新其显示状态
	if(!_ViewCube.IsNull())
	{
		SetViewCube(isVisible);
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
	//_ViewCube->SetSize(size * myViewport->DpiScale());
	//_ViewCube->SetBoxFacetExtension(size * myViewport->dpiScale() * 0.15);
	//_ViewCube->SetViewAnimation(myViewport->aisAnimationCamera());
	_ViewCube->SetFixedAnimationLoop(false);
	_ViewCube->SetDrawAxes(true);
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
		//    aisContext->SetViewAffinity(_ViewCube, viewport->v3dView(), viewport.get() == currentmyViewport.get());
		//}
	}

	//_WorkspaceController->invalidate(true);
}

void ViewportController::InitWindow()
{
	_UpdateParameter();
}

void ViewportController::_UpdateParameter()
{
	SetViewCube(true, 50, 2.0);
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

	myViewport->OnViewMoved();
}

void ViewportController::ZoomFitAll() 
{
	myViewport->GetV3dView()->FitAll(0.1, false);
	myViewport->GetV3dView()->ZFitAll(1.0);

	myViewport->OnViewMoved();
}

void ViewportController::Zoom(double value)
{
	if(value > 0)
	{
		myViewport->GetV3dView()->SetZoom(1.0 + value, true);
	}
	else if(value < 0)
	{
		myViewport->GetV3dView()->SetZoom(1.0 / (1.0 - value), true);
	}
	myViewport->GetV3dView()->Redraw();
	myViewport->OnViewMoved();
}
