// Copyright [2024] SunCAD

#ifndef IACT_COMMANDS_COMMANDHELPER_H_
#define IACT_COMMANDS_COMMANDHELPER_H_

//#include "Iact/Framework/Tool.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Workspace/ModelController.h"



class CommandHelper {
 public:
    static Handle(WorkspaceController) GetWorkspaceController();

    static Handle(ModelController) DocumentController();

    //static Tool* currentTool();

    //static bool startTool(Tool* tool);

    //static inline bool canExecuteOnWorkspace() {
    //    return workspaceController() && workspaceController()->workspace();
    //}

    static bool CanExecuteOnViewport();

    static bool CanStartTool();

};

#endif  // IACT_COMMANDS_COMMANDHELPER_H_
