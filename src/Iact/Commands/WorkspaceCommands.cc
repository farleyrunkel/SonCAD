// Copyright [2024] SunCAD

// Own include
#include "Iact/Commands/WorkspaceCommands.h"

#include "App/Resource.h"

ActionCommand& WorkspaceCommands::doUndo()
{
    static ActionCommand command;

    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Undo"));
        command.setIcon(Resource::icon("Edit/Edit-Undo"));
        command.setToolTip(QObject::tr("Revert the last operation."));
        command.setCheckable(false);
    }
    return command;
}

ActionCommand& WorkspaceCommands::doRedo()
{
    static ActionCommand command;
    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Redo"));
        command.setIcon(Resource::icon("Edit/Edit-Redo"));
        command.setToolTip(QObject::tr("Restore the last reverted operation."));
        command.setCheckable(false);
    }

    return command;
}

ActionCommand& WorkspaceCommands::setPredefinedView(ViewportController::PredefinedViews param)
{
    static ActionCommand command;
    return command;
}

ActionCommand& WorkspaceCommands::zoomFitAll()
{
    static ActionCommand command;

    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Zoom All"));
        command.setIcon(Resource::icon("View/Zoom-All"));
        command.setToolTip(QObject::tr("Adjusts the position and scale of the viewport so all visible entities are in view."));
        command.setCheckable(false);
    }

    return command;
}

ActionCommand& WorkspaceCommands::zoomIn()
{
    static ActionCommand command;
    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Zoom In"));
        command.setIcon(Resource::icon("View/Zoom-In"));
        command.setCheckable(false);
    }
    return command;
}

ActionCommand& WorkspaceCommands::zoomOut()
{
    static ActionCommand command;
    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Zoom Out"));
        command.setIcon(Resource::icon("View/Zoom-Out"));
        command.setCheckable(false);
    }
    return command;
}
