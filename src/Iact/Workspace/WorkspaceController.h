// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include <QObject>
#include <QList>

#include "Core/Workspace.h"
#include "Core/Viewport.h"
#include "Comm/BaseObject.h"
#include "Iact/Framework/Editor.h"
#include "Iact/Workspace/MouseEventData.h"

class Tool;
class ViewportController;

class WorkspaceController : public BaseObject {
    Q_OBJECT

 public:
    explicit WorkspaceController(QObject* parent = nullptr) : BaseObject(parent) {}

    explicit WorkspaceController(Workspace* workspace);

    void initWorkspace();

    Tool* currentTool() const;
    void removeTool(Tool* tool) {}
    bool startTool(Tool* tool);
    bool isSelecting() { return false; }
    void invalidate(bool immediateOnly = false, bool forceRedraw = false);
;
    bool cancelTool(Tool* tool, bool force);

    Workspace* workspace() const;

    void setActiveViewport(Viewport* viewport);

    ViewportController* viewportController(Viewport* viewport);

    void dispose();

    QList<WorkspaceControl*> enumerateControls();

private:
    void onWorkspaceGridChanged() {}
    void redraw();

    void MouseMove(ViewportController* viewportController, QPointF pos, Qt::Modifier modifierKeys);

private: 
    QList<ViewportController*> m_viewportControllers;
    MouseEventData* _MouseEventData;
    Tool* m_currentTool;
    Editor* m_currentEditor;
    Workspace* m_workspace;
    Viewport* m_activeViewport;
};

#endif // SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
