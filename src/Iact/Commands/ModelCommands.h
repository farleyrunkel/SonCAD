// Copyright [2024] SonCAD

#ifndef SRC_IACT_COMMANDS_MODELCOMMANDS_H_
#define SRC_IACT_COMMANDS_MODELCOMMANDS_H_

#include "Pres/Commands/ActionCommand.h"
#include <QMessageBox>

class ModelCommands {
 public:
    static ActionCommand& CreateBox();
};

#endif  // SRC_IACT_COMMANDS_MODELCOMMANDS_H_
