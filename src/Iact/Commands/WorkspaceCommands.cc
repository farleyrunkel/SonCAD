// Copyright [2024] SunCAD

// Own include
#include "Iact/Commands/WorkspaceCommands.h"

// Qt includes
#include <QIcon>
#include <QMessageBox>
#include <QObject>

// Project includes
#include "Iact/Commands/CommandHelper.h"
#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/Workspace/EditorState.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "App/ResourceUtils.h"

// Initialize the static command outside the class
ActionCommand& WorkspaceCommands::DoUndo()
{
    static ActionCommand command(
        []() { ; },
        []() { return false; }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Undo"));
        command.setIcon(Resource::Icon("Edit/Edit-Undo"));
        command.setToolTip(QObject::tr("Revert the last operation."));
        command.setCheckable(false);
    }

    return command;
}

ActionCommand& WorkspaceCommands::DoRedo()
{
    static ActionCommand command(
        []() { ; },
        []() { return false; }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Redo"));
        command.setIcon(Resource::Icon("Edit/Edit-Redo"));
        command.setToolTip(QObject::tr("Restore the last reverted operation."));
        command.setCheckable(false);
    }

    return command;
}

ActionCommand& WorkspaceCommands::SetTopView()
{
    static ActionCommand command(
        []() { InteractiveContext::Current()->GetViewportController()->SetPredefinedView(ViewportController::PredefinedViews::Top); },
        []() { return CommandHelper::CanExecuteOnViewport(); }
    );
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Top"));
        command.setIcon(Resource::Icon("View/View-Top"));
        command.setCheckable(false);
    }
    return command;
}

ActionCommand& WorkspaceCommands::SetBottomView()
{
    static ActionCommand command(
        []() { InteractiveContext::Current()->GetViewportController()->SetPredefinedView(ViewportController::PredefinedViews::Bottom); },
        []() { return CommandHelper::CanExecuteOnViewport(); }
    );
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Bottom"));
        command.setIcon(Resource::Icon("View/View-Bottom"));
        command.setCheckable(false);
    }
    return command;
}

ActionCommand& WorkspaceCommands::SetFrontView()
{
    static ActionCommand command(
        []() { InteractiveContext::Current()->GetViewportController()->SetPredefinedView(ViewportController::PredefinedViews::Front); },
        []() { return CommandHelper::CanExecuteOnViewport(); }
    );
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Front"));
        command.setIcon(Resource::Icon("View/View-Front"));
        command.setCheckable(false);
    }
    return command;
}

ActionCommand& WorkspaceCommands::SetBackView()
{
    static ActionCommand command(
        []() { InteractiveContext::Current()->GetViewportController()->SetPredefinedView(ViewportController::PredefinedViews::Back); },
        []() { return CommandHelper::CanExecuteOnViewport(); }
    );
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Back"));
        command.setIcon(Resource::Icon("View/View-Back"));
        command.setCheckable(false);
    }
    return command;
}

ActionCommand& WorkspaceCommands::SetRightView()
{
    static ActionCommand command(
        []() { InteractiveContext::Current()->GetViewportController()->SetPredefinedView(ViewportController::PredefinedViews::Right); },
        []() { return CommandHelper::CanExecuteOnViewport(); }
    );
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Right"));
        command.setIcon(Resource::Icon("View/View-Right"));
        command.setCheckable(false);
    }
    return command;
}

ActionCommand& WorkspaceCommands::SetLefttView()
{
    static ActionCommand command(
        []() { InteractiveContext::Current()->GetViewportController()->SetPredefinedView(ViewportController::PredefinedViews::Left); },
        []() { return CommandHelper::CanExecuteOnViewport(); }
    );
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Right"));
        command.setIcon(Resource::Icon("View/View-Right"));
        command.setCheckable(false);
    }
    return command;
}

ActionCommand& WorkspaceCommands::SetPredefinedView(ViewportController::PredefinedViews param)
{
    switch(param)
    {
    case ViewportController::PredefinedViews::Top:
        return SetTopView();
    case ViewportController::PredefinedViews::Bottom:
        return SetBottomView();
    case ViewportController::PredefinedViews::Front:
        return SetFrontView();
    case ViewportController::PredefinedViews::Back:
        return SetBackView();
    case ViewportController::PredefinedViews::Right:
        return SetRightView();
    default:
        return SetFrontView();
    }
}

ActionCommand& WorkspaceCommands::ZoomFitAll()
{
    static ActionCommand command(
        []() { InteractiveContext::Current()->GetViewportController()->ZoomFitAll(); },
        []() { return CommandHelper::CanExecuteOnViewport(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Zoom All"));
        command.setIcon(Resource::Icon("View/Zoom-All"));
        command.setToolTip(QObject::tr("Adjusts the position and scale of the viewport so all visible entities are in view."));
        command.setCheckable(false);
    }

    return command;
}

ActionCommand& WorkspaceCommands::ZoomFitSelected()
{
    static ActionCommand command(
        []() { InteractiveContext::Current()->GetViewportController()->ZoomFitAll(); },
        []() { return CommandHelper::CanExecuteOnViewport(); }
    );

    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Zoom Selection"));
        command.setIcon(Resource::Icon("View/Zoom-Selection"));
        command.setToolTip(QObject::tr("Adjusts the position and scale of the viewport so all visible and selected entities are in view."));
        command.setCheckable(false);
    }

    return command;
}

ActionCommand& WorkspaceCommands::ZoomIn()
{
    static ActionCommand command(
        []() { InteractiveContext::Current()->GetViewportController()->Zoom(0.5); },
        []() { return CommandHelper::CanExecuteOnViewport(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Zoom In"));
        command.setIcon(Resource::Icon("View/Zoom-In"));
        command.setCheckable(false);
    }

    return command;
}

ActionCommand& WorkspaceCommands::ZoomOut()
{
    static ActionCommand command(
        []() { InteractiveContext::Current()->GetViewportController()->Zoom(-0.5); },
        []() { return CommandHelper::CanExecuteOnViewport(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Zoom Out"));
        command.setIcon(Resource::Icon("View/Zoom-Out"));
        command.setCheckable(false);
    }

    return command;
}
