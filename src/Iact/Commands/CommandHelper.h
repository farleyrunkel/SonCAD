// Copyright [2024] SonCAD

#ifndef SRC_IACT_COMMANDS_COMMANDHELPER_H_
#define SRC_IACT_COMMANDS_COMMANDHELPER_H_

#include "App/Application.h"

#include "Iact/Framework/Tool.h"
#include "Iact/Workspace/WorkspaceController.h"

class CommandHelper {
public:
    static inline WorkspaceController* workspaceController() {
        return coreApp->appContext() ? coreApp->appContext()->workspaceController() : nullptr;
    }

    //static inline Tool* currentTool() {
    //    return workspaceController() ? workspaceController()->currentTool() : nullptr;
    //}

    static inline bool startTool(Tool* tool) {
        auto controller = workspaceController();
        return false;
    }

    //static inline bool canExecuteOnWorkspace() {
    //    return workspaceController() && workspaceController()->workspace();
    //}

    static inline bool canExecuteOnViewport() {
        return coreApp->appContext() && coreApp->appContext()->viewportController()
            && coreApp->appContext()->viewportController()->viewport();
    }

    static inline bool canStartTool() {
        return workspaceController() != nullptr;
    }

};

#endif  // SRC_IACT_COMMANDS_COMMANDHELPER_H_
