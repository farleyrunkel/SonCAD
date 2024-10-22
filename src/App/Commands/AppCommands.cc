// Copyright [2024] SunCAD

#include <QMessageBox>

#include "App/Application.h"
#include "App/Commands/AppCommands.h"

#include "Iact/Commands/CommandHelper.h"
#include "Iact/Commands/DocumentCommands.h"

RelayCommand& AppCommands::initApplication() {
    static RelayCommand command(
        []() {
            DocumentCommands::CreateNewModel().execute();
        }
    );

    return command;
}
