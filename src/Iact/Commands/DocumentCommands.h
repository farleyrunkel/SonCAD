// Copyright [2024] SunCAD

#ifndef IACT_COMMANDS_DOCUMENTCOMMANDS_H_
#define IACT_COMMANDS_DOCUMENTCOMMANDS_H_

#include "Pres/Commands/ActionCommand.h"


class DocumentCommands {
public:
    static ActionCommand& CreateNewModel();
    static ActionCommand& OpenModelFrom();
};

#endif  // IACT_COMMANDS_DOCUMENTCOMMANDS_H_
