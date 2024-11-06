// Copyright [2024] SunCAD

#include "Iact/Workspace/WorkspaceController.h"

#include <algorithm>

#include <QDebug>

#include "Iact/Workspace/ViewportController.h"
#include "Iact/Framework/Tool.h"

WorkspaceController::WorkspaceController(Workspace* workspace):
    _MouseEventData(nullptr),
    m_currentTool(nullptr),
    m_currentEditor(nullptr),
    m_activeViewport(nullptr),
    m_workspace(workspace) {
    connect(m_workspace, &Workspace::gridChanged, this, &WorkspaceController::onWorkspaceGridChanged);

    initWorkspace();
}

void WorkspaceController::initWorkspace() {
    // 初始化 V3dViewer 和 AisContext
    workspace()->initV3dViewer();
    workspace()->initAisContext();
    // initVisualSettings();

    // 遍历所有 Viewport 并添加到 _viewControllers 列表
    for (auto& view : workspace()->viewports()) {
        m_viewportControllers.append(new ViewportController(view, this));
    }

    // 创建并显示网格
    //_grid = new AISX_Grid();
    //AisHelper::disableGlobalClipPlanes(_grid);
    //if (workspace.aisContext()) {
    //    workspace.aisContext()->Display(_grid, 0, -1, false);
    //}

    //// 初始化 VisualObjects 并更新网格
    //visualObjects.initEntities();
    //updateGrid();
}

Tool* WorkspaceController::currentTool() const { return m_currentTool; }


bool WorkspaceController::startTool(Tool* tool) {
    try {
        if (currentTool() != nullptr && !cancelTool(currentTool(), true)) {
            return false;
        }
        if (tool != nullptr) {
            tool->setWorkspaceController(this);
            m_currentTool = tool;
            if (m_currentEditor) { m_currentEditor->stopTool(); }
            if (!tool->start()) {
                return false;
            }

            invalidate(true);
            return true;
        }
        return false;
    }
    catch (std::exception& e) {
        qDebug() << e.what();
        return false;
    }
}

void WorkspaceController::invalidate(bool immediateOnly, bool forceRedraw)
{
    m_workspace->setNeedsImmediateRedraw(true);
    if (!immediateOnly)
        m_workspace->setNeedsRedraw(true);

    if (forceRedraw)
        redraw();
}

void WorkspaceController::redraw() {
}

void WorkspaceController::mouseMove(ViewportController* viewportController, QPointF pos, Qt::KeyboardModifiers modifiers)
{
    for (const auto& handler : enumerateControls())
    {
        if (handler->onMouseMove(_MouseEventData))
            break;
    }
}

bool WorkspaceController::cancelTool(Tool* tool, bool force) {
    return true;
}

Workspace* WorkspaceController::workspace() const { return m_workspace; }

void WorkspaceController::setActiveViewport(Viewport* viewport) {
     m_activeViewport = viewport;
 }

ViewportController* WorkspaceController::viewportController(Viewport* viewport) {
    if (viewport == nullptr) {
        return nullptr;
    }

    auto it = std::find_if(m_viewportControllers.begin(), m_viewportControllers.end(),
        [viewport](const ViewportController* vc) {
            return vc->viewport() == viewport;
        });

    return (it != m_viewportControllers.end()) ? *it : nullptr;
}

void WorkspaceController::dispose() {}

QList<WorkspaceControl*> WorkspaceController::enumerateControls() {
    QList<WorkspaceControl*> controls;

    if (m_currentTool) {
        controls.push_back(m_currentTool);
    }

    if (m_currentEditor) {
        controls.push_back(m_currentEditor);
    }

    return controls;
}
