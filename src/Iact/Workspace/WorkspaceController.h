// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include <QList>
#include <QObject>

#include "Comm/BaseObject.h"
#include "Core/Viewport.h"
#include "Core/Workspace.h"
#include "Iact/Framework/Editor.h"
#include "Iact/HudElements/IHudManager.h"
#include "Iact/Visual/VisualObjectManager.h"
#include "Iact/Workspace/MouseEventData.h"
#include "Occt/AisExtensions/AISX_Grid.h"
#include "Occt/OcctHelper/AisHelper.h"

#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_XY.hxx>

class Marker;
class Tool;
class Sun_ViewportController;
class Sun_WorkspaceController;

DEFINE_STANDARD_HANDLE(Sun_WorkspaceController, Standard_Transient);

class Sun_WorkspaceController : public Sun_BaseObject
{
    Q_OBJECT
    Q_PROPERTY(Sun::Sun_Workspace* Sun_Workspace READ Sun_Workspace CONSTANT)
    Q_PROPERTY(Sun_Viewport* ActiveViewport READ ActiveViewport WRITE SetActiveViewport NOTIFY ActiveViewportChanged)
    //Q_PROPERTY(ViewportController* ActiveViewController READ ActiveViewControlller CONSTANT)
    //Q_PROPERTY(IHudManager* HudManager READ HudManager WRITE SetHudManager NOTIFY HudManagerChanged)
    //Q_PROPERTY(bool LockWorkingPlane READ LockWorkingPlane WRITE SetLockWorkingPlane NOTIFY LockWorkingPlaneChanged)
    //Q_PROPERTY(SelectionManager* Selection READ Selection CONSTANT)
    //Q_PROPERTY(bool IsSelecting READ IsSelecting WRITE SetIsSelecting NOTIFY IsSelectingChanged)
    Q_PROPERTY(Sun_VisualObjectManager* VisualObjects READ VisualObjects CONSTANT)
    Q_PROPERTY(gp_Pnt CursorPosition READ CursorPosition WRITE SetCursorPosition NOTIFY CursorPositionChanged)
    Q_PROPERTY(gp_Pnt2d CursorPosition2d READ CursorPosition2d WRITE SetCursorPosition2d NOTIFY CursorPosition2dChanged)

public:
    explicit Sun_WorkspaceController(Sun::Sun_Workspace* workspace);
    ~Sun_WorkspaceController() {}

public:
    void InitWorkspace();

    Tool* currentTool() const;
    void removeTool(Tool* tool) {}
    bool startTool(Tool* tool);
    bool IsSelecting() { return false; }
    void Invalidate(bool immediateOnly = false, bool forceRedraw = false);

    bool cancelTool(Tool* tool, bool force);

    IHudManager* hudManager() const { return _HudManager; }
    void setHudManager(IHudManager* hudManager);

    void SetActiveViewport(Sun_Viewport* Viewport);

    Sun_ViewportController* viewportController(Sun_Viewport* Viewport);

    void dispose();

    QList<WorkspaceControl*> enumerateControls();

    void MouseMove(Sun_ViewportController* viewportController, QPointF pos, Qt::KeyboardModifiers modifiers);
    void MouseDown(Sun_ViewportController* viewportController, Qt::KeyboardModifiers modifiers);
    void MouseUp(Sun_ViewportController* viewportController, Qt::KeyboardModifiers modifiers);

    void recalculateGridSize();

public:
    Sun::Sun_Workspace* Sun_Workspace() const;
    Sun_Viewport* ActiveViewport() const { return _ActiveViewport; }
    Sun_VisualObjectManager* VisualObjects() const { return _VisualObjectManager; }
    gp_Pnt CursorPosition() const { return _CursorPosition; }
    void SetCursorPosition(const gp_Pnt& pnt) {}
    gp_Pnt2d CursorPosition2d() const { return _CursorPosition2d; }
    void SetCursorPosition2d(const gp_Pnt2d& pnt2d) {}

private:
    void _Workspace_GridChanged(Sun::Sun_Workspace *);
    void _Viewport_ViewportChanged(Sun_Viewport*);
    void _Redraw();
    void _UpdateGrid();
    void initVisualSettings();
    void _RecalculateGridSize() {}
    void _UpdateParameter() {}
    void _RedrawTimer_Tick() {}

signals:
    void ActiveViewportChanged(Sun_Viewport*);
    void CursorPositionChanged(const gp_Pnt&);
    void CursorPosition2dChanged(const gp_Pnt2d&);

private:
    Tool* _CurrentTool;
    Editor* _CurrentEditor;
    Sun::Sun_Workspace* _Workspace;
    Sun_Viewport* _ActiveViewport;
    IHudManager* _HudManager;
    Sun_VisualObjectManager* _VisualObjectManager;

    QTimer* _RedrawTimer;

    bool _GridNeedsUpdate;
    Handle(AISX_Grid) _Grid;
    gp_XY _LastGridSize = gp_XY(1000.0, 1000.0);

private:
    QList<Sun_ViewportController*> _ViewportControllers;

    MouseEventData _MouseEventData;
    QPointF _LastMouseMovePosition;
    Sun_ViewportController* _LastMouseMoveViewportController;
    Qt::Modifiers _LastModifierKeys;
    Handle(AIS_InteractiveObject) _LastDetectedAisObject;
    Handle(SelectMgr_EntityOwner) _LastDetectedOwner;
    gp_Pnt _CursorPosition;
    gp_Pnt2d _CursorPosition2d;
};

#endif // SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
