// Copyright [2024] SunCAD

#include "Iact/Commands/DocumentCommands.h"

#include <QIcon>
#include <QObject>
#include <QMessageBox>

#include "ResourceUtils.h"
#include "App/Application.h"
#include "Iact/Commands/CommandHelper.h"


ActionCommand& DocumentCommands::CreateNewModel() {
    static ActionCommand command(
        []() { if (CommandHelper::documentController()->askForSavingModelChanges()) {
                    CommandHelper::documentController()->newModel();
            }
        },
        []() { return CommandHelper::documentController() != nullptr; }
    );

    if (command.text().isEmpty()) {
        command.setText(QObject::tr("New Model"));
        command.setToolTip(QObject::tr("Create a new model."));
        command.setIcon(ResourceUtils::icon("App/App-NewModel"));
    }

    return command;
}