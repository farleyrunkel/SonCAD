// Copyright [2024] SonCAD

#ifndef SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include <QObject>

#include "Core/Workspace.h"
#include "Iact/Framework/Tool.h"

class WorkspaceController : public QObject {
    Q_OBJECT

 public:
    explicit WorkspaceController(QObject* parent = nullptr);

    void dispose();
};

#endif // SRC_IACT_WORKSPACE_WORKSPACECONTROLLER_H_
