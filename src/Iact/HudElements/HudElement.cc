// Copyright [2024] SunCAD

#include "Iact/HudElements/HudElement.h"

#include "Iact/Workspace/WorkspaceController.h"

Handle(WorkspaceController) HudElement::GetWorkspaceController() const
{
	return myWorkspaceController;
}

void HudElement::SetWorkspaceController(const Handle(WorkspaceController)& controller)
{
	if(myWorkspaceController && myWorkspaceController != controller)
	{
		throw std::logic_error("workspaceController cannot be changed");
	}
	myWorkspaceController = controller;
}
