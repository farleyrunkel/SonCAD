// Copyright [2024] SunCAD

#ifndef SRC_APP_COMMANDS_APPCOMMANDS_H_
#define SRC_APP_COMMANDS_APPCOMMANDS_H_

#include "Pres/Commands/ActionCommand.h"
#include "Pres/Commands/RelayCommand.h"

class AppCommands {
 public:
    static RelayCommand& initApplication();

};

#endif  // SRC_APP_COMMANDS_APPCOMMANDS_H_
