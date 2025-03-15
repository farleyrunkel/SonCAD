// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include <QList>
#include <QObject>

#include "Comm/BaseObject.h"
#include "Core/Workspace.h"
#include "Iact/Framework/Tool.h"

DEFINE_STANDARD_HANDLE(WorkspaceController, BaseObject)

class WorkspaceController : public BaseObject
{
public:
    WorkspaceController();
    WorkspaceController(const Handle(Workspace)& value) {}

    bool StartTool(Handle(Tool) tool);

    Handle(Tool) CurrentTool();
    void Invalidate();

    Handle(Workspace) GetWorkspace();
};

#endif // IACT_WORKSPACE_WORKSPACECONTROLLER_H_
