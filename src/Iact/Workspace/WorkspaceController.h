// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include <QObject>

#include "Core/Workspace.h"
#include "Comm/BaseObject.h"
#include "Iact/Framework/Tool.h"
#include "Iact/Framework/Editor.h"

class WorkspaceController : public BaseObject {
    Q_OBJECT

 public:
    explicit WorkspaceController(Workspace* workspace) {
        m_workspace = workspace;
        connect(m_workspace, &Workspace::gridChanged, this, &WorkspaceController::onWorkspaceGridChanged);

    };

    Tool* currentTool() const;

    bool startTool(Tool* tool);

    void invalidate(bool immediateOnly = false, bool forceRedraw = false);

    void _Redraw();;
    bool cancelTool(Tool* tool, bool force);

    Workspace* workspace() const;

    void dispose();
private:
    void onWorkspaceGridChanged() {}

private: 
    Tool* m_currentTool;
    Editor* m_editor;
    Workspace* m_workspace;
};

#endif // SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
