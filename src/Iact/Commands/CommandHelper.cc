// Copyright [2024] SunCAD

#include "Iact/Commands/CommandHelper.h"

#include "App/Application.h"

Handle(WorkspaceController) CommandHelper::GetWorkspaceController()
{
    return App->GetAppContext() ? App->GetAppContext()->GetWorkspaceController() : nullptr;
}

Handle(ModelController) CommandHelper::GetDocumentController()
{
    return App->GetAppContext() ? App->GetAppContext()->GetDocumentController() : nullptr;
}

Handle(Tool) CommandHelper::CurrentTool()
{
    return GetWorkspaceController() ? GetWorkspaceController()->CurrentTool() : nullptr;
}

bool CommandHelper::StartTool(Handle(Tool) tool)
{
    return GetWorkspaceController() && GetWorkspaceController()->StartTool(tool);
}

inline bool CommandHelper::CanExecuteOnWorkspace()
{
    return GetWorkspaceController() && GetWorkspaceController()->GetWorkspace();
}

bool CommandHelper::CanExecuteOnViewport()
{
    return App->GetAppContext() && App->GetAppContext()->GetViewportController()
        && App->GetAppContext()->GetViewportController()->GetViewport();
}

bool CommandHelper::CanStartTool()
{
    return !GetWorkspaceController().IsNull();
}
