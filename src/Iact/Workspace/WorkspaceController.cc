// Copyright [2024] SunCAD

#include "Iact/Workspace/WorkspaceController.h"

#include "Comm/BaseObject.h"
#include "Core/Workspace.h"
#include "Iact/Framework/Tool.h"
#include "Iact/Visual/VisualObjectManager.h"
#include "Occt/OcctHelper/AisHelper.h"

WorkspaceController::WorkspaceController()
{}

bool WorkspaceController::StartTool(const Handle(Tool)& tool)
{
	tool->SetWorkspaceController(this);

	tool->Start();

    return false;
}

Handle(Tool) WorkspaceController::CurrentTool()
{
    return nullptr;
}

Handle(Workspace) WorkspaceController::GetWorkspace()
{
    return _Workspace;
}

// GetViewController

Handle(ViewportController) WorkspaceController::GetViewController(int index)
{
    return _ViewControllers[index];
}

Handle(ViewportController) WorkspaceController::GetViewController(const Handle(Viewport)& viewport)
{
    if(viewport.IsNull())
    {
        return nullptr;
    }

    auto it = std::find_if(_ViewControllers.begin(), _ViewControllers.end(),
                           [viewport](const auto& vc) {
        return vc->GetViewport() == viewport;
    });

	return (it == _ViewControllers.end()) ? nullptr: *it;
}

void WorkspaceController::InitWorkspace()
{
	_Workspace->InitV3dViewer();
	_Workspace->InitAisContext();

    for(auto& view : _Workspace->GetViewports())
    {
        Handle(ViewportController) viewCtrl = new ViewportController(view, this);
		_ViewControllers.Append(viewCtrl);
    }
}

void WorkspaceController::SetActiveViewport(const Handle(Viewport)& viewport)
{
	_ActiveViewport = viewport;
}

Handle(Viewport) WorkspaceController::ActiveViewport() const
{
	return _ActiveViewport;
}

NCollection_Vector<Handle(WorkspaceControl)> WorkspaceController::EnumerateControls()
{
    qDebug() << "Debug: m_workspaceController::enumerateControls";
    NCollection_Vector<Handle(WorkspaceControl)> controls;

    if(m_currentTool)
    {
        controls.Append(m_currentTool);
    }

    if(m_currentEditor)
    {
        controls.Append(m_currentEditor);
    }

    return controls;
}

void WorkspaceController::MouseMove(const Handle(ViewportController)& viewportController,
                                    const Graphic3d_Vec2d& pos, 
                                    Aspect_VKeyFlags modifierKeys)
{
    qDebug() << "Debug: m_workspaceController::MouseMove: " << pos;

    _LastMouseMovePosition = pos;
	_LastMouseMoveViewportController = viewportController;
    _LastModifierKeys = modifierKeys;
	_MouseEventData->Clear();

    for(auto& aisObject : _CustomHighlights)
    {
        if(_Workspace->AisContext()->IsDisplayed(aisObject))
        {
			_Workspace->AisContext()->Unhilight(aisObject, false);
        }
    }

	_CustomHighlights.Clear();

	if(pos.x() < 0 || pos.y() < 0)
	{
        _Workspace->AisContext()->MoveTo(0, 0, viewportController->GetViewport()->V3dView(), false);
        Invalidate(true);
        return;
	}

	auto status = _Workspace->AisContext()->MoveTo(pos.x(), pos.y(), viewportController->GetViewport()->V3dView(), false);

	Invalidate(true);

	if(status == AIS_StatusOfDetection::AIS_SOD_Error)
	{
		_CursorPosition = gp_Pnt();
		_CursorPosition2d = gp_Pnt2d();
        return;
	}

    gp_Pnt planePoint;
    
	if(!viewportController->GetViewport()->ScreenToPoint(_Workspace->WorkingPlane(), pos.x(), pos.y(), planePoint))
	{
        _CursorPosition = gp_Pnt();
        _CursorPosition2d = gp_Pnt2d();
	}

    _LastDetectedAisObject.Nullify();
    _LastDetectedOwner.Nullify();

	_MouseEventData->Set(viewportController->GetViewport(), pos, planePoint, modifierKeys);

    if(_Workspace->AisContext()->HasDetected())
    {
		_LastDetectedOwner = _Workspace->AisContext()->DetectedOwner();
		_LastDetectedAisObject = _Workspace->AisContext()->DetectedInteractive();
		TopoDS_Shape detectedShape = AisHelper::GetShapeFromEntityOwner(_LastDetectedOwner);
		_LastDetectedAisObject->SetOwner(_LastDetectedOwner);

		auto detectedEntity = _VisualObjects->GetEntity(_LastDetectedAisObject);

    }

    for(const auto& handler : EnumerateControls())
    {
        if(handler->OnMouseMove(_MouseEventData)) {
        }
    }
}

void WorkspaceController::MouseDown(const Handle(ViewportController)& VC, Aspect_VKeyFlags keys) 
{}

void WorkspaceController::MouseUp(const Handle(ViewportController)& VC, Aspect_VKeyFlags keys)
{}
