// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include <QList>
#include <QObject>

#include "Comm/BaseObject.h"
#include "Core/Workspace.h"

DEFINE_STANDARD_HANDLE(WorkspaceController, BaseObject)

class WorkspaceController : public BaseObject
{
public:
    WorkspaceController() {}
    ~WorkspaceController() {}
    void Dispose() {
    }

    void Invalidate() {}

    Handle(Workspace) Workspace() {
        return nullptr;
    }
};

#endif // IACT_WORKSPACE_WORKSPACECONTROLLER_H_
