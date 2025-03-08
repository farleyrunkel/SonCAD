// Copyright [2024] SunCAD

#ifndef IACT_COMMANDS_DOCUMENTCOMMANDS_H_
#define IACT_COMMANDS_DOCUMENTCOMMANDS_H_

#include <memory>

#include <QObject>

#include "App/Resource.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Pres/Commands/ActionCommand.h"

class DocumentCommands
{
public:
    static ActionCommand& createNewModel()
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
};

#endif  // IACT_COMMANDS_DOCUMENTCOMMANDS_H_
