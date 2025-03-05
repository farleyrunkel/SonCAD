// Copyright [2024] SunCAD

// Own include
#include "Pres/Commands/ActionCommand.h"

#include <QAction>

#include "Pres/Commands/RelayCommand.h"

// Constructor
ActionCommand::ActionCommand(std::function<void()> execute, std::function<bool()> canExecute)
    : QAction(nullptr)
    , RelayCommand(execute, canExecute)
{
    // connect the triggered signal to execute
    connect(this, &QAction::triggered, [this]() {
        if (this->canExecute()) {
            this->execute();
        }
    });
}
