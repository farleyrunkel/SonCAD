// Copyright [2024] SonCAD

#ifndef APP_ACTIONCOMMAND_H
#define APP_ACTIONCOMMAND_H

#include <functional>

#include <QAction>

#include "App/Application.h"
#include "Pres/Commands/RelayCommand.h"

class ActionCommand final : public QAction, public RelayCommand {
    Q_OBJECT

public:
    // Constructor
    ActionCommand(std::function<void()> execute, std::function<bool()> canExecute)
        : QAction(), RelayCommand(execute, canExecute)
    {
        connect(this, &QAction::triggered, [this]() {this->execute(); });
        connect(coreApp->commandManager(), &CommandManager::updateEnabled, 
            [this]() {this->setEnabled(this->canExecute()); });
    }
};

#endif  // APP_ACTIONCOMMAND_H
