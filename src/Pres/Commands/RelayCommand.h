// Copyright [2024] SunCAD

#ifndef SRC_PRES_COMMANDS_RELAYCOMMAND_H_
#define SRC_PRES_COMMANDS_RELAYCOMMAND_H_

#include <functional>
#include <utility>

#include "Intf/ICommand.h"

class RelayCommand : public ICommand {
 public:
     // Constructor
    RelayCommand(std::function<void()> execute);

    // Constructor
    RelayCommand(std::function<void()> execute, std::function<bool()> canExecute);

    // Method to execute the command
    void execute() override;

    // Method to check if the command can be executed
    bool canExecute() const override;

 private:
    std::function<void()> _execute;      // Function to execute the command
    std::function<bool()> _canExecute;   // Function to check if the command can be executed
};

#endif  // SRC_PRES_COMMANDS_RELAYCOMMAND_H_
