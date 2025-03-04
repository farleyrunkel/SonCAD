// Copyright [2024] SunCAD

#ifndef IACT_COMMANDS_DOCUMENTCOMMANDS_H_
#define IACT_COMMANDS_DOCUMENTCOMMANDS_H_

#include "Pres/Commands/ActionCommand.h"

class DocumentCommands 
{
public:
    static ActionCommand& createNewModel()
    {
        static ActionCommand command;
        return command;
    }

    static ActionCommand& openModelFrom()
    {
        static ActionCommand command;
        return command;
    }
};

#endif  // IACT_COMMANDS_DOCUMENTCOMMANDS_H_
