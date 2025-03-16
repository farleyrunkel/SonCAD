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

	if(m_viewCube.IsNull())
		return;

	if(isVisible && !aisContext->IsDisplayed(m_viewCube))
	{
		aisContext->Display(m_viewCube, false);
		//_WorkspaceController->invalidate(true);
	}
	else if(!isVisible && aisContext->IsDisplayed(m_viewCube))
	{
		aisContext->Remove(m_viewCube, false);
		//_WorkspaceController->invalidate(true);
	}
}

void ViewportController::SetViewCube(bool isVisible, int size, double duration)
{
	auto aisContext = myViewport->GetWorkspace()->AisContext();

	// 如果视图立方体已存在，则使用现有方法更新其显示状态
	if(!m_viewCube.IsNull())
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
	m_viewCube = new AIS_ViewCube();
	//m_viewCube->SetSize(size * myViewport->DpiScale());
	//m_viewCube->SetBoxFacetExtension(size * myViewport->dpiScale() * 0.15);
	//m_viewCube->SetViewAnimation(myViewport->aisAnimationCamera());
	m_viewCube->SetFixedAnimationLoop(false);
	m_viewCube->SetDrawAxes(true);
	m_viewCube->SetDuration(duration);
	m_viewCube->SetResetCamera(true);
	m_viewCube->SetFitSelected(true);
	//m_viewCube->SetTexture(pixmap);

	// 设置位置及透视效果
	m_viewCube->SetTransformPersistence(new Graphic3d_TransformPers(
		Graphic3d_TMF_TriedronPers, Aspect_TOTP_RIGHT_UPPER, Graphic3d_Vec2i(100, 100)));

	// 配置颜色
	Quantity_Color sideColor, edgeColor, cornerColor;
	Quantity_Color::ColorFromHex("d9dfe5", sideColor);
	Quantity_Color::ColorFromHex("93a4b6", edgeColor);
	Quantity_Color::ColorFromHex("a6b4c3", cornerColor);

	m_viewCube->BoxSideStyle()->SetColor(sideColor);
	m_viewCube->BoxEdgeStyle()->SetColor(edgeColor);
	m_viewCube->BoxCornerStyle()->SetColor(cornerColor);

	// 设置材质
	auto material = new Graphic3d_MaterialAspect(Graphic3d_NOM_DEFAULT);
	material->SetAmbientColor(Quantity_Color(0.8, 0.8, 0.8, Quantity_TOC_sRGB));
	material->SetDiffuseColor(Quantity_Color(0.2, 0.2, 0.2, Quantity_TOC_sRGB));
	material->SetEmissiveColor(Quantity_NOC_BLACK);
	material->SetSpecularColor(Quantity_NOC_BLACK);
	m_viewCube->SetMaterial(*material);

	// 高亮属性
	auto highlightColor = Colors::Highlight;
	m_viewCube->DynamicHilightAttributes()->ShadingAspect()->SetColor(highlightColor);
	m_viewCube->DynamicHilightAttributes()->ShadingAspect()->SetMaterial(*material);

	// 显示或隐藏视图立方体
	if(isVisible)
	{
		aisContext->Display(m_viewCube, false);

		//for (const auto& viewport : _WorkspaceController->workspace()->viewports()) {
		//    aisContext->SetViewAffinity(m_viewCube, viewport->v3dView(), viewport.get() == currentmyViewport.get());
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
