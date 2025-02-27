// Copyright [2024] SunCAD

#include "Iact/HudElements/HudElement.h"

#include "Iact/Workspace/WorkspaceController.h"



	Handle(WorkspaceController) IHudElement::GetGetWorkspaceController() const {
		return _WorkspaceController;
	}

	void IHudElement::setWorkspaceController(const Handle(WorkspaceController)& controller) {
		if (!_WorkspaceController.IsNull()  && _WorkspaceController != controller) {
			throw std::logic_error("Sun_WorkspaceController cannot be changed");
		}
		_WorkspaceController = controller;
	}
