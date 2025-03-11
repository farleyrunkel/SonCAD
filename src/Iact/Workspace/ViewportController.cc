
#include "Iact/Workspace/ViewportController.h"

#include <cmath>

#include <AIS_RubberBand.hxx>
#include <Aspect_RenderingContext.hxx>
#include <Aspect_Window.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <NCollection_Vec2.hxx>
#include <NCollection_Vector.hxx>

#include <WNT_WClass.hxx>
#include <WNT_Window.hxx>

#include "Core/Project/Viewport.h"
#include "Core/Project/VisualStyles.h"
#include "Core/Project/Workspace.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Occt/OcctExtensions/AIS_ViewCubeEx.h"

ViewportController::ViewportController(const std::shared_ptr<Viewport>& viewport, const std::shared_ptr<WorkspaceController>& WC)
	: myViewport(viewport)
	, myWorkspaceController(WC)
	, _LockedToPlane(false)
	, _ShowTrihedron(false)
	, _RubberbandIncludeTouched(false)
	, IsInRubberbandSelection(false)
	, myRubberbandSelectionMode(RubberbandSelectionMode::Rectangle)
	, _ZoomFitAllOnInit(false)
{
	init();
}

std::shared_ptr<Viewport> ViewportController::viewport() const
{
	return myViewport;
}

void ViewportController::init()
{
	viewport()->init(true);
}

Handle(Aspect_Window) ViewportController::window() const
{
	return !view().IsNull() ? view()->Window() : nullptr;
}

void ViewportController::SetWindow(const Handle(Aspect_Window)& theWindow, const Aspect_RenderingContext theContext)
{
	if(!view().IsNull())
	{
		view()->SetWindow(theWindow, theContext);
	}
}

Handle(AIS_ViewCube) ViewportController::viewCube() const
{
	return m_viewCube;
}

void ViewportController::setViewCube(bool isVisible)
{
    auto aisContext = workspaceController()->workspace()->aisContext();

    if(m_viewCube.IsNull())
        return;

    if(isVisible && !aisContext->IsDisplayed(m_viewCube))
    {
        aisContext->Display(m_viewCube, false);
        workspaceController()->invalidate(true);
    }
    else if(!isVisible && aisContext->IsDisplayed(m_viewCube))
    {
        aisContext->Remove(m_viewCube, false);
        workspaceController()->invalidate(true);
    }
}

void ViewportController::setViewCube(bool isVisible, int size, double duration)
{
    auto aisContext = myWorkspaceController->workspace()->aisContext();

    // 如果视图立方体已存在，则使用现有方法更新其显示状态
    if(!m_viewCube.IsNull())
    {
        setViewCube(isVisible);
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
    m_viewCube = new AIS_ViewCubeEx();
    m_viewCube->SetSize(size * viewport()->dpiScale());
    m_viewCube->SetBoxFacetExtension(size * viewport()->dpiScale() * 0.15);
    m_viewCube->SetViewAnimation(viewport()->aisAnimationCamera());
    m_viewCube->SetFixedAnimationLoop(false);
    m_viewCube->SetDrawAxes(false);
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

        //for (const auto& viewport : workspaceController()->workspace()->viewports()) {
        //    aisContext->SetViewAffinity(m_viewCube, viewport->v3dView(), viewport.get() == currentViewport().get());
        //}
    }

    workspaceController()->invalidate();
}
