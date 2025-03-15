// Copyright [2024] SunCAD

#include "Iact/Workspace/ViewportController.h"

ViewportController::ViewportController(const Handle(Viewport)& viewport, const Handle(WorkspaceController)& wc)
{
	myViewport = viewport;
	_WorkspaceController = wc;
}
