// Copyright [2024] SunCAD

#include "Iact/Commands/DocumentCommands.h"

#include "App/Resource.h"

ActionCommand& DocumentCommands::createNewModel()
{
    static ActionCommand cmd([] {
        auto context = InteractiveContext::current();
        auto controller = context->documentController();
        if(controller && controller->askForSavingModelChanges())
        {
            controller->newModel();
        }
    }, [] {
        auto context = InteractiveContext::current();
        return context->documentController() != nullptr;
    });

    if(cmd.text().isEmpty())
    {
        cmd.setText(QObject::tr("New Model"));
        cmd.setIcon(Resource::icon("App/App-NewModel"));
        cmd.setToolTip(QObject::tr("Create a new model."));
    }
    return cmd;
}
