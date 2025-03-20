// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include <vector>

#include <Aspect_VKeyFlags.hxx>
#include <Graphic3d_Vec2.hxx>
#include <Graphic3d_Vec4.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <NCollection_Vector.hxx>

#include "Comm/BaseObject.h"
#include "Core/Workspace.h"
#include "Iact/Framework/Editor.h"
#include "Iact/Framework/Tool.h"
#include "Iact/Visual/VisualObjectManager.h"
#include "Iact/Workspace/MouseEventData.h"
#include "Iact/Workspace/Selection/SelectionManager.h"
#include "Iact/Workspace/ViewportController.h"

DEFINE_STANDARD_HANDLE(WorkspaceController, BaseObject)

class WorkspaceController : public BaseObject
{
public:
    WorkspaceController();
    WorkspaceController(const Handle(Workspace)& value)
    {
        _Workspace = value;
        InitWorkspace();
    }

    bool StartTool(const Handle(Tool)& tool);

    Handle(Tool) CurrentTool();
    void Invalidate(bool immediateOnly = false, bool forceRedraw = false)
    {}

    void SelectByRectangle(const Graphic3d_Vec4i& corners, bool includeTouched, const Handle(ViewportController)& viewportController) {}
    void SelectByPolyline(const std::vector<Graphic3d_Vec2i>& pointList, bool includeTouched, const Handle(ViewportController)& viewportController) {}

    Handle(Workspace) GetWorkspace();

    // GetViewController
    Handle(ViewportController) GetViewController(int index);

    Handle(ViewportController) GetViewController(const Handle(Viewport)& viewport);

    void InitWorkspace();

    void SetActiveViewport(const Handle(Viewport)& viewport);

    Handle(Viewport) ActiveViewport() const;

    NCollection_Vector<Handle(WorkspaceControl)> EnumerateControls();
    // mouse control
public:
    void MouseMove(const Handle(ViewportController)& VC, const Graphic3d_Vec2d& pos, Aspect_VKeyFlags keys);
    void MouseDown(const Handle(ViewportController)& VC, Aspect_VKeyFlags keys);
    void MouseUp(const Handle(ViewportController)& VC, Aspect_VKeyFlags keys);

private:
    NCollection_Vector<Handle(ViewportController)> _ViewControllers;

    Handle(Workspace) _Workspace;
    Handle(Viewport) _ActiveViewport;

private:
    Handle(Tool)  m_currentTool;
    Handle(Editor) m_currentEditor;

    std::shared_ptr<MouseEventData> _MouseEventData;

    Graphic3d_Vec2d _LastMouseMovePosition;
    Handle(ViewportController) _LastMouseMoveViewportController;
    Aspect_VKeyFlags _LastModifierKeys;

    // _CustomHighlights
    NCollection_Vector<Handle(AIS_InteractiveObject)> _CustomHighlights;

	Handle(SelectionManager) _SelectionManager;

    gp_Pnt  _CursorPosition;
    gp_Pnt2d _CursorPosition2d;
};

#endif // IACT_WORKSPACE_WORKSPACECONTROLLER_H_
