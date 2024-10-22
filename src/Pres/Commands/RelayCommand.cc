// Copyright [2024] SunCAD

#include "Pres/Commands/RelayCommand.h"

RelayCommand::RelayCommand(std::function<void()> execute)
    : _execute(std::move(execute)), _canExecute(nullptr) {
}

RelayCommand::RelayCommand(std::function<void()> execute, std::function<bool()> canExecute)
    : _execute(std::move(execute)), _canExecute(std::move(canExecute)) {
}

void RelayCommand::execute() {
    if (_execute) {
        _execute();
    }
}

bool RelayCommand::canExecute() const {
    return _canExecute ? _canExecute() : true;
}
