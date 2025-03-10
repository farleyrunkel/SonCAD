
#include "Iact/Workspace/WorkspaceController.h"

#include <algorithm>

#include "Occt/OcctHelper/AisHelper.h"
#include "Core/Project/VisualStyles.h"

WorkspaceController::WorkspaceController()
    : enable_shared_from_this<WorkspaceController>()
{}

WorkspaceController::WorkspaceController(const std::shared_ptr<Workspace>& workspace)
    : enable_shared_from_this<WorkspaceController>()
    , m_workspace(workspace)
{
    assert(m_workspace != nullptr);
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

}

std::shared_ptr<Workspace> WorkspaceController::workspace() const
{
    return m_workspace;
}
