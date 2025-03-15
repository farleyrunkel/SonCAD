// Copyright [2024] SunCAD

#include "Iact/Workspace/WorkspaceController.h"

#include "Comm/BaseObject.h"
#include "Core/Workspace.h"
#include "Iact/Framework/Tool.h"

WorkspaceController::WorkspaceController()
{}

bool WorkspaceController::StartTool(Handle(Tool) tool)
{
    return false;
}

Handle(Tool) WorkspaceController::CurrentTool()
{
    return nullptr;

}

void WorkspaceController::Invalidate()
{}

Handle(Workspace) WorkspaceController::GetWorkspace()
{
    return nullptr;
}

// GetViewController

Handle(ViewportController) WorkspaceController::GetViewController(int index)
{
    return _ViewControllers[index];
}

Handle(ViewportController) WorkspaceController::GetViewController(const Handle(Viewport)& viewport)
{
	for(auto& vc : _ViewControllers)
	{
		if(vc->GetViewport() == viewport)
		{
			return vc;
		}
	}
	return nullptr;
}

void WorkspaceController::InitWorkspace()
{
    for(auto& view : _Workspace->GetViewports())
    {
        Handle(ViewportController) viewCtrl = new ViewportController(view, this);
		_ViewControllers.Append(viewCtrl);
    }
}

