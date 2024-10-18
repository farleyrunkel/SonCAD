// Copyright [2024] SonCAD

#include "Iact/Commands/ModelCommands.h"

#include <QIcon>
#include <QObject>
#include <QMessageBox>

#include "ResourceUtils.h"
#include "App/Application.h"
#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/Commands/CommandHelper.h"

// Initialize the static command outside the class
ActionCommand& ModelCommands::CreateBox() {
    static ActionCommand command (
        []() { CommandHelper::startTool(new CreateBoxTool()); },
        []() { return CommandHelper::canStartTool(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Box"));
        command.setIcon(ResourceUtils::icon(ResourceUtils::MODEL_BOX));
        command.setToolTip(QObject::tr("Creates a new body with a box shape."));

        command.connect(coreApp->commandManager(), &CommandManager::updateEnabled,
            []() { command.setEnabled(command.canExecute()); }
        );

        command.connect(coreApp->appContext(), &InteractiveContext::workspaceControllerChanged,
            []() {
                command.setCheckable(
                    qobject_cast<CreateBoxTool*>(coreApp->appContext()->workspaceController()) != nullptr
                );
            }
        );
    }
    return command;
}
