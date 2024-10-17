// Copyright [2024] SonCAD

#ifndef IACT_WorkspaceController_H
#define IACT_WorkspaceController_H

#include <QObject>

class WorkspaceController : public QObject
{
    Q_OBJECT

public:
    WorkspaceController(QObject* parent = nullptr) : QObject(parent) {}
    ~WorkspaceController() {}
    void dispose() {
        // 释放资源的具体逻辑
    }
};

#endif // IACT_WorkspaceController_H
