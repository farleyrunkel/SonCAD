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
#include "Iact/HudElements/IHudManager.h"
#include "Occt/AisExtensions/AISX_Grid.h"
#include "Occt/OcctHelper/AisHelper.h"

#include <gp_XY.hxx>

class Marker;
class Tool;
class ViewportController;

class WorkspaceController : public BaseObject {
    Q_OBJECT

 public:
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

    void setHudManager(IHudManager* hudManager);
    void setActiveViewport(Viewport* viewport);

    ViewportController* viewportController(Viewport* viewport);

    void dispose();

    QList<WorkspaceControl*> enumerateControls();

    void mouseMove(ViewportController* viewportController, QPointF pos, Qt::KeyboardModifiers modifiers);
    void mouseDown(ViewportController* viewportController, Qt::KeyboardModifiers modifiers);
    void mouseUp(ViewportController* viewportController, Qt::KeyboardModifiers modifiers);

    void recalculateGridSize();
 private:
    void onWorkspaceGridChanged(Workspace*);
    void _Redraw();
    void _UpdateGrid();
    void initVisualSettings();

 private: 
    QList<ViewportController*> m_viewportControllers;
    MouseEventData* m_mouseEventData;
    Tool* m_currentTool;
    Editor* m_currentEditor;
    Workspace* m_workspace;
    Viewport* m_activeViewport;
    IHudManager* m_hudManager;

    bool _GridNeedsUpdate;
    Handle(AISX_Grid) _Grid;
    gp_XY _LastGridSize = gp_XY(200.0, 200.0);
};

#endif // SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
