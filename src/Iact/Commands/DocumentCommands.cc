// Copyright [2024] SunCAD

#include "Iact/Commands/DocumentCommands.h"

#include <QIcon>
#include <QObject>
#include <QMessageBox>

#include "App/ResourceUtils.h"
#include "App/Application.h"
#include "Iact/Commands/CommandHelper.h"

ActionCommand& DocumentCommands::CreateNewModel()
{
    static ActionCommand command(
        []() {
        if(auto DC = InteractiveContext::Current()->GetDocumentController(); DC->AskForSavingModelChanges())
            DC->NewModel();
    },
        []() { return CommandHelper::CanCreateDocument(); }
    );

    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("New Model"));
        command.setToolTip(QObject::tr("Create a new model."));
        command.setIcon(Resource::Icon("App/App-NewModel"));
    }

    return command;
}

ActionCommand& DocumentCommands::OpenModelFrom()
{
    static ActionCommand command(
        []() { if(InteractiveContext::Current()->GetDocumentController()->AskForSavingModelChanges())
    {
        InteractiveContext::Current()->GetDocumentController()->OpenModelFrom("");
    }},
        []() { return !InteractiveContext::Current()->GetDocumentController().IsNull(); }
    );

    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Open Model..."));
        command.setToolTip(QObject::tr("Opens an existing Model."));
        command.setIcon(Resource::Icon("App/App-OpenModel"));
    }

    return command;
}
