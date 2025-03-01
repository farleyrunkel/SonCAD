// Copyright [2024] SunCAD

#ifndef IACT_COMMANDS_COMMANDHELPER_H_
#define IACT_COMMANDS_COMMANDHELPER_H_

//#include "Iact/Framework/Tool.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Workspace/ModelController.h"
#include "Iact/Framework/Tool.h"


class CommandHelper
{
public:
    static Handle(WorkspaceController) GetWorkspaceController();

    static Handle(ModelController) GetDocumentController();

    static Handle(Tool) CurrentTool();

    static bool StartTool(Handle(Tool) tool);

    static inline bool CanExecuteOnWorkspace();

    static bool CanExecuteOnViewport();

    static bool CanStartTool();

};

#endif  // IACT_COMMANDS_COMMANDHELPER_H_
