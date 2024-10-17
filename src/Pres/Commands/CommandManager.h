// Copyright [2024] SonCAD

#ifndef PRES_COMMANDS_COMMANDMANAGER_H
#define PRES_COMMANDS_COMMANDMANAGER_H

#include <functional>

#include <QObject>

class CommandManager final : public QObject {
    Q_OBJECT
public:
    // Constructor
    CommandManager()
    {
    }
signals:
    void updateEnabled();
};

#endif  // PRES_COMMANDS_COMMANDMANAGER_H
