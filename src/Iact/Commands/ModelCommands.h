// Copyright [2024] SunCAD

#ifndef IACT_COMMANDS_MODELCOMMANDS_H_
#define IACT_COMMANDS_MODELCOMMANDS_H_

// Project includes
#include "Pres/Commands/ActionCommand.h"

class ModelCommands 
{
public:
    static ActionCommand& createBox()
    {
        static ActionCommand command;
        return command;
    }
    static ActionCommand& createCylinder()
    {
        static ActionCommand command;
        return command;
    }
    static ActionCommand& createSphere()
    {
        static ActionCommand command;
        return command;
    }
};

#endif  // IACT_COMMANDS_MODELCOMMANDS_H_
