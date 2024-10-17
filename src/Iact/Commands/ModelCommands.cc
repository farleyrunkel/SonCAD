// Copyright [2024] SonCAD

#include "Iact/Commands/ModelCommands.h"

#include <QIcon>
#include <QObject>

#include "App/Application.h"
#include "Iact/Primitives/CreateBoxTool.h"

// Initialize the static command outside the class
ActionCommand& ModelCommands::CreateBox() {
    static ActionCommand command(
        []() {
            // Show a warning message for box creation
            QMessageBox::warning(nullptr, QObject::tr("Create Box"), QObject::tr("This is a warning about creating a box."));
        },
        []() {
            // Check if the command can be executed
            return true;
        }
    );

    // Set text and icon if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Box"));
        command.setIcon(QIcon("://icons/model/Prim-Box.svg"));
        command.setToolTip(QObject::tr("Creates a new body with a box shape."));

        // Update checkable state based on workspace controller
        command.connect(coreApp->appContext(), &InteractiveContext::workspaceControllerChanged,
            []() {
                command.setCheckable(qobject_cast<CreateBoxTool*>(coreApp->appContext()->workspaceController()));
            });
    }

    return command;
}
