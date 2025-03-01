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
