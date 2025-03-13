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
    static ActionCommand& createNewModel();
};

#endif  // IACT_COMMANDS_DOCUMENTCOMMANDS_H_
