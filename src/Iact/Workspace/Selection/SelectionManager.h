#ifndef IACT_WORKSPACE_SELECTION_SELECTIONMANAGER_H_
#define IACT_WORKSPACE_SELECTION_SELECTIONMANAGER_H_

#include <NCollection_Vector.hxx>

#include "Comm/BaseObject.h"
#include "Core/Topology/InteractiveEntity.h"

class WorkspaceController;

DEFINE_STANDARD_HANDLE(SelectionManager, BaseObject)

class SelectionManager : public BaseObject
{
public:
    enum SelectionMode
    {
        Exclusive,
        Add,
        Toggle
    };

public:
	SelectionManager(const Handle(WorkspaceController)& workspaceController)
	{

    }

private:
    NCollection_Vector<Handle(InteractiveEntity)> _EmptyList;
	Handle(WorkspaceController) _WorkspaceController;
};

#endif // !IACT_WORKSPACE_SELECTION_SELECTIONMANAGER_H_
