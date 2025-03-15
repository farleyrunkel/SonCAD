// Copyright [2024] SunCAD

#include "Iact/Commands/CommandHelper.h"

#include "App/Application.h"
#include "Iact/Workspace/InteractiveContext.h"

Handle(Tool) CommandHelper::CurrentTool()
{
    return InteractiveContext::Current()->GetWorkspaceController()
        ? InteractiveContext::Current()->GetWorkspaceController()->CurrentTool() 
        : nullptr;
}

bool CommandHelper::StartTool(Handle(Tool) tool)
{
    return InteractiveContext::Current()->GetWorkspaceController() 
        && InteractiveContext::Current()->GetWorkspaceController()->StartTool(tool);
}

bool CommandHelper::CanExecuteOnWorkspace()
{
    return InteractiveContext::Current()->GetWorkspaceController() 
        && InteractiveContext::Current()->GetWorkspaceController()->GetWorkspace();
}

bool CommandHelper::CanExecuteOnViewport()
{
    return InteractiveContext::Current()->GetViewportController()
        && InteractiveContext::Current()->GetViewportController()->GetViewport();
}

bool CommandHelper::CanCreateDocument()
{
    return !InteractiveContext::Current()->GetDocumentController().IsNull();
}

bool CommandHelper::CanStartTool()
{
    return !InteractiveContext::Current()->GetWorkspaceController().IsNull();
}
