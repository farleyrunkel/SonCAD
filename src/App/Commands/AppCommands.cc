// Copyright [2024] SunCAD

#include <QIcon>

#include "ResourceUtils.h"
#include "App/Application.h"
#include "App/Commands/AppCommands.h"
#include "Core/Core.h"
#include "Iact/Commands/CommandHelper.h"
#include "Iact/Commands/DocumentCommands.h"

ActionCommand& AppCommands::showAboutDialog() {
    static AboutDialog aboutDialog(nullptr);
    static ActionCommand command(
        []() { aboutDialog.show(); }
    );
    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("About SunCAD..."));
        command.setToolTip(QObject::tr("Shows version and license information."));
        command.setIcon(ResourceUtils::icon("App/App-AboutDialog"));
    }
    return command;
}

ActionCommand& AppCommands::exitApplication() {
    static ActionCommand command(
        []() { Core::mainWindow()->close(); }
    );
    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Exit Program"));
        command.setIcon(ResourceUtils::icon("App/App-ExitApp"));
    }
    return command;
}

RelayCommand& AppCommands::initApplication() {
    static RelayCommand command(
        []() { DocumentCommands::CreateNewModel().execute(); }
    );

    return command;
}
