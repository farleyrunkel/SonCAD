// Copyright [2024] SonCAD

#ifndef APP_RELAYCOMMAND_H
#define APP_RELAYCOMMAND_H

#include <functional>

#include "Intf/ICommand.h"

class RelayCommand : public ICommand {
public:
    // Constructor
    RelayCommand(std::function<void()> execute, std::function<bool()> canExecute)
        : _execute(std::move(execute)), _canExecute(std::move(canExecute))
    {
    }

    // Method to execute the command
    void execute() override {
        if (_execute) {
            _execute();
        }
    }

    // Method to check if the command can be executed
    bool canExecute() const override {
        return _canExecute ? _canExecute() : true;
    }

private:
    std::function<void()> _execute;      // Function to execute the command
    std::function<bool()> _canExecute;   // Function to check if the command can be executed
};

#endif  // APP_ACTIVECOMMAND_H
