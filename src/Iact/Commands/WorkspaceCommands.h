// Copyright [2024] SunCAD

#ifndef IACT_COMMANDS_WORKSPACECOMMANDS_H_
#define IACT_COMMANDS_WORKSPACECOMMANDS_H_

// Project includes
#include "Iact/Workspace/ViewportController.h"
#include "Pres/Commands/ActionCommand.h"

class WorkspaceCommands
{
public:
    static ActionCommand& doUndo()
    {
        static ActionCommand command;
        return command;
    }
    static ActionCommand& doRedo()
    {
        static ActionCommand command;
        return command;
    }
    static ActionCommand& setPredefinedView(ViewportController::PredefinedViews param)
    {
        static ActionCommand command;
        return command;
    }
    static ActionCommand& zoomFitAll()
    {
        static ActionCommand command;
        return command;
    }
    static ActionCommand& zoomIn()
    {
        static ActionCommand command;
        return command;
    }
    static ActionCommand& zoomOut()
    {
        static ActionCommand command;
        return command;
    }
};

#endif  // IACT_COMMANDS_WORKSPACECOMMANDS_H_
