// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include <QObject>
#include <QList>

#include "Core/Workspace.h"
#include "Core/Viewport.h"
#include "Comm/BaseObject.h"
#include "Iact/Framework/Tool.h"
#include "Iact/Framework/Editor.h"

class ViewportController;
class WorkspaceController : public BaseObject {
    Q_OBJECT

 public:
    explicit WorkspaceController(QObject* parent = nullptr) : BaseObject(parent) {}

    explicit WorkspaceController(Workspace* workspace);;

    Tool* currentTool() const;

    bool startTool(Tool* tool);

    void invalidate(bool immediateOnly = false, bool forceRedraw = false);

    void _Redraw();;
    bool cancelTool(Tool* tool, bool force);

    Workspace* workspace() const;

    void setActiveViewport(Viewport* viewport);

    ViewportController* viewportController(Viewport* viewport);

    void dispose();
private:
    void onWorkspaceGridChanged() {}

private: 
    Tool* m_currentTool;
    Editor* m_editor;
    Workspace* m_workspace;
    Viewport* m_activeViewport;
    QList<ViewportController*> _viewControllers;
};

#endif // SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
