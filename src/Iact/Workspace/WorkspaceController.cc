
#include "Iact/Workspace/WorkspaceController.h"

#include "Occt/OcctHelper/AisHelper.h"

WorkspaceController::WorkspaceController()
    : enable_shared_from_this<WorkspaceController>()
{}

WorkspaceController::WorkspaceController(const std::shared_ptr<Workspace>& workspace)
    : enable_shared_from_this<WorkspaceController>()
    , m_workspace(workspace)
{
    assert(m_workspace != nullptr);
}

void WorkspaceController::setActiveViewport(const std::shared_ptr<Viewport>& value) {}

std::shared_ptr<ViewportController> WorkspaceController::getViewController(const std::shared_ptr<Viewport>& value)
{
	return nullptr;
}

void WorkspaceController::initWorkspace() {
    // init V3dViewer and aisContext
    //m_workspace->initV3dViewer();
    //m_workspace->initAisContext();
    //initVisualSettings();

    auto a = shared_from_this();
    // 遍历所有 viewport 并添加到 _viewControllers 列表
    for(auto& view : m_workspace->viewports())
    {
        m_viewportControllers.push_back(std::make_shared<ViewportController>(view, shared_from_this()));
    }

    // 创建并显示网格
    m_grid = new AISX_Grid();

    AisHelper::disableGlobalClipPlanes(m_grid);

    //if(m_workspace->aisContext())
    //{
    //    m_workspace->aisContext()->Display(m_grid, 0, -1, false);
    //}

    //// 初始化 VisualObjects 并更新网格
    //visualObjects.initEntities();
    updateGrid();
}


void WorkspaceController::initVisualSettings()
{

}

void WorkspaceController::updateGrid()
{

}