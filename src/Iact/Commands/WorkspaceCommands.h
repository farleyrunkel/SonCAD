// Copyright [2024] SunCAD

#ifndef IACT_COMMANDS_WORKSPACECOMMANDS_H_
#define IACT_COMMANDS_WORKSPACECOMMANDS_H_

// Project includes
#include "Iact/Workspace/ViewportController.h"
#include "Pres/Commands/ActionCommand.h"

class WorkspaceCommands
{
public:
    static ActionCommand& DoUndo();
    static ActionCommand& DoRedo();
    static ActionCommand& SetPredefinedView(ViewportController::PredefinedViews param);
    static ActionCommand& SetTopView();
    static ActionCommand& SetBottomView();
    static ActionCommand& SetFrontView();
    static ActionCommand& SetBackView();
    static ActionCommand& SetRightView();
    static ActionCommand& SetLefttView();
    static ActionCommand& ZoomFitAll();
    static ActionCommand& ZoomFitSelected();
    static ActionCommand& ZoomIn();
    static ActionCommand& ZoomOut();
};

#endif  // IACT_COMMANDS_WORKSPACECOMMANDS_H_
