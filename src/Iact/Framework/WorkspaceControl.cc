
#include "Iact/Framework/WorkspaceControl.h"

WorkspaceControl::WorkspaceControl() {}

// workspaceController

std::shared_ptr<WorkspaceController> WorkspaceControl::workspaceController() const
{
	return myWorkspaceController;
}

void WorkspaceControl::setWorkspaceController(const std::shared_ptr<WorkspaceController>& value) { myWorkspaceController = value; }
