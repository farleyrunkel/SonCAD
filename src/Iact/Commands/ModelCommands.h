// Copyright [2024] SonCAD

#ifndef APP_MODELCOMMANDS_H
#define APP_MODELCOMMANDS_H

#include "Pres/Commands/ActionCommand.h"
#include <QMessageBox>

class ModelCommands {
public:
    // ���徲̬�� ActionCommand
    static ActionCommand& CreateBox();
};

#endif  // APP_MODELCOMMANDS_H
