// Copyright [2024] SunCAD

#include "Iact/Workspace/WorkspaceController.h"

#include <QDebug>


Tool* WorkspaceController::currentTool() const { return m_currentTool; }


 bool WorkspaceController::startTool(Tool* tool) {
    try {
        //if (currentTool() != nullptr && !cancelTool(currentTool(), true)) {
        //    return false;
        //}
        //if (tool != nullptr) {
        //    tool->setWorkspaceController(this);
        //    m_currentTool = tool;
        //    if (m_editor) { m_editor->stopTool(); }
        //    if (!tool->start()) {
        //        return false;
        //    }

        //    invalidate(true);
        //    return true;
        //}
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
        _Redraw();
}

 void WorkspaceController::_Redraw() {}

 bool WorkspaceController::cancelTool(Tool* tool, bool force)
{
    return true;
}

 Workspace* WorkspaceController::workspace() const { return m_workspace; }

void WorkspaceController::dispose() {}
