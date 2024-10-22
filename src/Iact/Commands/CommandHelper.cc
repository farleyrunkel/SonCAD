// Copyright [2024] SunCAD

#include "Iact/Commands/CommandHelper.h"

#include "App/Application.h"

 WorkspaceController* CommandHelper::workspaceController() {
    return coreApp->appContext() ? coreApp->appContext()->workspaceController() : nullptr;
}

 ModelController* CommandHelper::documentController() {
    return coreApp->appContext() ? coreApp->appContext()->documentController() : nullptr;
}

 Tool* CommandHelper::currentTool() {
    return workspaceController() ? workspaceController()->currentTool() : nullptr;
}

 bool CommandHelper::startTool(Tool* tool) {
    return workspaceController() && workspaceController()->startTool(tool);
}

 bool CommandHelper::canExecuteOnViewport() {
    return coreApp->appContext() && coreApp->appContext()->viewportController()
        && coreApp->appContext()->viewportController()->viewport();
}

 bool CommandHelper::canStartTool() {
    return workspaceController() != nullptr;
}
