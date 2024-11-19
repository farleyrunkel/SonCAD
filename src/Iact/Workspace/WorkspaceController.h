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
class WorkspaceController;

class VisualObjectManager {
public:
    VisualObjectManager(WorkspaceController*) {}
};

class WorkspaceController : public QObject
{
    Q_OBJECT
        Q_PROPERTY(Sun::Workspace* Workspace READ Workspace CONSTANT)
        Q_PROPERTY(Viewport* ActiveViewport READ ActiveViewport WRITE SetActiveViewport NOTIFY ActiveViewportChanged)
        //Q_PROPERTY(ViewportController* ActiveViewController READ ActiveViewControlller CONSTANT)
        //Q_PROPERTY(IHudManager* HudManager READ HudManager WRITE SetHudManager NOTIFY HudManagerChanged)
        //Q_PROPERTY(bool LockWorkingPlane READ LockWorkingPlane WRITE SetLockWorkingPlane NOTIFY LockWorkingPlaneChanged)
        //Q_PROPERTY(SelectionManager* Selection READ Selection CONSTANT)
        //Q_PROPERTY(bool IsSelecting READ IsSelecting WRITE SetIsSelecting NOTIFY IsSelectingChanged)
        Q_PROPERTY(VisualObjectManager* VisualObjects READ VisualObjects CONSTANT)
        //Q_PROPERTY(Pnt ? CursorPosition READ CursorPosition WRITE SetCursorPosition NOTIFY CursorPositionChanged)
        //Q_PROPERTY(Pnt2d ? CursorPosition2d READ CursorPosition2d WRITE SetCursorPosition2d NOTIFY CursorPosition2dChanged)

public:
    explicit WorkspaceController(Sun::Workspace* workspace);
    ~WorkspaceController() {}

public:
    void InitWorkspace();

    Tool* currentTool() const;
    void removeTool(Tool* tool) {}
    bool startTool(Tool* tool);
    bool isSelecting() { return false; }
    void Invalidate(bool immediateOnly = false, bool forceRedraw = false);
    ;
    bool cancelTool(Tool* tool, bool force);

    IHudManager* hudManager() const { return _HudManager; }

    void setHudManager(IHudManager* hudManager);
    void SetActiveViewport(Viewport* viewport);

    ViewportController* viewportController(Viewport* viewport);

    void dispose();

    QList<WorkspaceControl*> enumerateControls();

    void mouseMove(ViewportController* viewportController, QPointF pos, Qt::KeyboardModifiers modifiers);
    void mouseDown(ViewportController* viewportController, Qt::KeyboardModifiers modifiers);
    void mouseUp(ViewportController* viewportController, Qt::KeyboardModifiers modifiers);

    void recalculateGridSize();

public:
    Sun::Workspace* Workspace() const;
    Viewport* ActiveViewport() const { return _ActiveViewport; }
    VisualObjectManager* VisualObjects() const { return _VisualObjectManager; }

private:
    void _Workspace_GridChanged(Sun::Workspace *);
    void _Viewport_ViewportChanged(Viewport*);
    void _Redraw();
    void _UpdateGrid();
    void initVisualSettings();
    void _RecalculateGridSize() {}
    void _UpdateParameter() {}
    void _RedrawTimer_Tick() {}

signals:
    void ActiveViewportChanged(Viewport*);

private:
    Tool* _CurrentTool;
    Editor* _CurrentEditor;
    Sun::Workspace* _Workspace;
    Viewport* _ActiveViewport;
    IHudManager* _HudManager;
    VisualObjectManager* _VisualObjectManager;

    QTimer* _RedrawTimer;

    bool _GridNeedsUpdate;
    Handle(AISX_Grid) _Grid;
    gp_XY _LastGridSize = gp_XY(200.0, 200.0);

private:
    QList<ViewportController*> _ViewportControllers;

    MouseEventData* _MouseEventData;
    QPointF _LastMouseMovePosition;
    ViewportController* _LastMouseMoveViewportController;
    Qt::Modifiers _LastModifierKeys;
    Handle(AIS_InteractiveObject) _LastDetectedAisObject;
    Handle(SelectMgr_EntityOwner) _LastDetectedOwner;
    gp_Pnt _CursorPosition;
    gp_Pnt2d _CursorPosition2d;
};


#endif // SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
