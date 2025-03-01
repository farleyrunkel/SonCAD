// Copyright [2024] SunCAD

#include "Iact/Commands/CommandHelper.h"

#include "Core/Core.h"

Handle(WorkspaceController) CommandHelper::GetWorkspaceController()
{
    return Core::GetAppContext() ? Core::GetAppContext()->GetWorkspaceController() : nullptr;
}

Handle(ModelController) CommandHelper::GetDocumentController()
{
    return Core::GetAppContext() ? Core::GetAppContext()->GetDocumentController() : nullptr;
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
    return Core::GetAppContext() && Core::GetAppContext()->GetViewportController()
        && Core::GetAppContext()->GetViewportController()->GetViewport();
}

bool CommandHelper::CanStartTool()
{
    return !GetWorkspaceController().IsNull();
}
