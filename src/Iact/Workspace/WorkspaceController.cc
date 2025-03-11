
#include "Iact/Workspace/WorkspaceController.h"

#include <algorithm>

#include "Core/Project/VisualStyles.h"
#include "Core/Project/WorkingContext.h"
#include "Occt/OcctHelper/AisHelper.h"

WorkspaceController::WorkspaceController(const std::shared_ptr<Workspace>& workspace)
    : m_workspace(workspace)
{
    assert(m_workspace != nullptr);
}

std::shared_ptr<ViewportController> WorkspaceController::getViewController(int idx) const
{
    if(idx < 0 || idx >= m_viewportControllers.size())
    {
        return nullptr;
    }
    return m_viewportControllers[idx];
}

void WorkspaceController::setActiveViewport(const std::shared_ptr<Viewport>& value) 
{
    m_activeViewport = value;
}

std::shared_ptr<ViewportController> WorkspaceController::getViewController(const std::shared_ptr<Viewport>& value)
{
    if(value == nullptr)
    {
        return nullptr;
    }

    auto found = std::find_if(m_viewportControllers.begin(), m_viewportControllers.end(), [value](const auto& VC) {return VC->viewport() == value;});

    if(found == m_viewportControllers.end())
    {
        return nullptr;
    }
    return *found;
}

void WorkspaceController::initWorkspace()
{
    // init V3dViewer and aisContext
    m_workspace->initV3dViewer();
    m_workspace->initAisContext();
    initVisualSettings();

    // 遍历所有 viewport 并添加到 _viewControllers 列表
    for(auto& view : m_workspace->viewports())
    {
        m_viewportControllers.emplace_back(std::make_shared<ViewportController>(view, shared_from_this()));
    }

    // 创建并显示网格
    m_grid = new AISX_Grid();

    AisHelper::disableGlobalClipPlanes(m_grid);

    if(auto context = m_workspace->aisContext(); !context.IsNull())
    {
        context->Display(m_grid, 0, -1, false);
    }

    //// 初始化 VisualObjects 并更新网格
    //visualObjects.initEntities();
    updateGrid();
}

void WorkspaceController::initVisualSettings()
{
    auto aisContext = m_workspace->aisContext();

    // updateParameter();

    // Higlight Selected
    auto selectionDrawer = new Prs3d_Drawer();
    selectionDrawer->SetupOwnDefaults();
    selectionDrawer->SetColor(Colors::Selection);
    selectionDrawer->SetDisplayMode(0);
    selectionDrawer->SetZLayer(0); // Graphic3d_ZLayerId_Default
    selectionDrawer->SetTypeOfDeflection(Aspect_TypeOfDeflection::Aspect_TOD_RELATIVE);
    selectionDrawer->SetDeviationAngle(aisContext->DeviationAngle());
    selectionDrawer->SetDeviationCoefficient(aisContext->DeviationCoefficient());
    aisContext->SetSelectionStyle(selectionDrawer);
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_Selected, selectionDrawer);
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_LocalSelected, selectionDrawer);
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_SubIntensity, selectionDrawer);

    // Higlight Dynamic
    auto hilightDrawer = new Prs3d_Drawer();
    hilightDrawer->SetupOwnDefaults();
    hilightDrawer->SetColor(Colors::Highlight);
    hilightDrawer->SetDisplayMode(0);
    hilightDrawer->SetZLayer(-2); // Graphic3d_ZLayerId_Top
    hilightDrawer->SetTypeOfDeflection(Aspect_TypeOfDeflection::Aspect_TOD_RELATIVE);
    hilightDrawer->SetDeviationAngle(aisContext->DeviationAngle());
    hilightDrawer->SetDeviationCoefficient(aisContext->DeviationCoefficient());
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_Dynamic, hilightDrawer);

    // Higlight Local
    auto hilightLocalDrawer = new Prs3d_Drawer();
    hilightLocalDrawer->SetupOwnDefaults();
    hilightLocalDrawer->SetColor(Colors::Highlight);
    hilightLocalDrawer->SetDisplayMode(1);
    hilightLocalDrawer->SetZLayer(-2); // Graphic3d_ZLayerId_Top
    hilightLocalDrawer->SetTypeOfDeflection(Aspect_TypeOfDeflection::Aspect_TOD_RELATIVE);
    hilightLocalDrawer->SetDeviationAngle(aisContext->DeviationAngle());
    hilightLocalDrawer->SetDeviationCoefficient(aisContext->DeviationCoefficient());

    auto shadingAspect = new Prs3d_ShadingAspect();
    shadingAspect->SetColor(Colors::Highlight);
    shadingAspect->SetTransparency(0);
    shadingAspect->Aspect()->SetPolygonOffsets(Aspect_PolygonOffsetMode::Aspect_POM_Fill, 0.99f, 0.0f);
    hilightLocalDrawer->SetShadingAspect(shadingAspect);

    auto lineAspect = new Prs3d_LineAspect(Colors::Highlight, Aspect_TypeOfLine::Aspect_TOL_SOLID, 3.0);
    hilightLocalDrawer->SetLineAspect(lineAspect);
    hilightLocalDrawer->SetSeenLineAspect(lineAspect);
    hilightLocalDrawer->SetWireAspect(lineAspect);
    hilightLocalDrawer->SetFaceBoundaryAspect(lineAspect);
    hilightLocalDrawer->SetFreeBoundaryAspect(lineAspect);
    hilightLocalDrawer->SetUnFreeBoundaryAspect(lineAspect);
    //hilightLocalDrawer->SetPointAspect(Marker::CreateBitmapPointAspect(Marker::BallImage(), Colors::Highlight));

    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_LocalDynamic, hilightLocalDrawer);
}


void WorkspaceController::updateGrid()
{
    if(!m_gridNeedsUpdate)
        return;

    if(m_grid.IsNull())
        return;

    auto wc = workspace()->workingContext();

    if(workspace()->gridEnabled())
    {
        gp_Ax3 position = wc->workingPlane().Position();
        if(wc->gridRotation() != 0)
        {
            position.Rotate(wc->workingPlane().Axis(), wc->gridRotation());
        }
        m_grid->SetPosition(position);
        m_grid->SetExtents(m_lastGridSize.X(), m_lastGridSize.Y());
        m_grid->SetDivisions(wc->gridStep(), wc->gridDivisions() * M_PI / 180.0);

        if(wc->gridType() == Workspace::GridTypes::Rectangular)
        {
            workspace()->aisContext()->SetDisplayMode(m_grid, 1, false);
        }
        else
        {
            workspace()->aisContext()->SetDisplayMode(m_grid, 2, false);
        }
    }
    else
    {
        workspace()->aisContext()->SetDisplayMode(m_grid, 0, false);
    }

    m_gridNeedsUpdate = false;
}

std::shared_ptr<Workspace> WorkspaceController::workspace() const
{
    return m_workspace;
}


void WorkspaceController::redraw()
{
    // 更新网格
    updateGrid();

    // 如果没有 V3dViewer，则直接返回
    if(workspace()->v3dViewer().IsNull())
        return;

    // 遍历所有视口，检查动画相机是否停止
    for(auto& v : workspace()->viewports())
    {
        if(!v->aisAnimationCamera()->IsStopped())
        {
            // 如果动画相机未停止，则更新计时器
            v->aisAnimationCamera()->UpdateTimer();
            workspace()->setNeedsRedraw(true);
        }
    }

    // 如果需要重新绘制
    if(workspace()->needsRedraw())
    {
        // 更新无效实体
        m_visualObjectManager->updateInvalidatedEntities();

        // 遍历所有视口，渲染 HLR 模式下的视口
        for(auto& v : workspace()->viewports())
        {
            if(v->renderMode() == Viewport::RenderModes::HLR)
                v->v3dView()->Update();
        }

        // 重绘并立即重绘视图
        workspace()->v3dViewer()->Redraw();
        workspace()->v3dViewer()->RedrawImmediate();

        // 标记不再需要重绘
        workspace()->setNeedsRedraw(false);
    }
    // 如果需要立即重绘
    else if(workspace()->needsImmediateRedraw())
    {
        // 立即重绘视图
        workspace()->v3dViewer()->RedrawImmediate();

        // 标记不再需要立即重绘
        workspace()->setNeedsImmediateRedraw(false);
    }
}

void WorkspaceController::invalidate(bool immediateOnly, bool forceRedraw)
{
    m_workspace->setNeedsImmediateRedraw(true);
    if(!immediateOnly)
        m_workspace->setNeedsRedraw(true);

    if(forceRedraw)
        redraw();
}
