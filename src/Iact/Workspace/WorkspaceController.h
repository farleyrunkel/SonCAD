// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_WORKSPACECONTROLLER_H_
#define IACT_WORKSPACE_WORKSPACECONTROLLER_H_

#include <QList>
#include <QObject>

#include <NCollection_Vector.hxx>

#include "Comm/BaseObject.h"
#include "Core/Workspace.h"
#include "Iact/Framework/Tool.h"
#include "Iact/Workspace/ViewportController.h"

DEFINE_STANDARD_HANDLE(WorkspaceController, BaseObject)

class WorkspaceController : public BaseObject
{
public:
    WorkspaceController();
    WorkspaceController(const Handle(Workspace)& value) 
    {
        _Workspace = value;
        InitWorkspace();
    }

    bool StartTool(Handle(Tool) tool);

    Handle(Tool) CurrentTool();
    void Invalidate();

    Handle(Workspace) GetWorkspace();

    // GetViewController
	Handle(ViewportController) GetViewController(int index);

	Handle(ViewportController) GetViewController(const Handle(Viewport)& viewport);

    void InitWorkspace();

	void SetActiveViewport(const Handle(Viewport)& viewport)
	{
		_ActiveViewport = viewport;
	}

private:
    NCollection_Vector<Handle(ViewportController)> _ViewControllers;

    Handle(Workspace) _Workspace;
    Handle(Viewport) _ActiveViewport;
};

#endif // IACT_WORKSPACE_WORKSPACECONTROLLER_H_
