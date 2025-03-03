#ifndef SelectionManager_H
#define SelectionManager_H

#include <vector>

#include <Standard_Transient.hxx>

#include "Core/Topology/InteractiveEntity.h"
#include "Iact/Workspace/Selection/SelectionContext.h"

class WorkspaceController;

DEFINE_STANDARD_HANDLE(SelectionManager, Standard_Transient)

class SelectionManager : public Standard_Transient
{
public:
    enum SelectionMode
    {
        Exclusive,
        Add,
        Toggle
    };

public:
    SelectionManager() {}

private:
    std::vector<Handle(InteractiveEntity)> myEmptyList;

    Handle(WorkspaceController) myWorkspaceController;

    // SelectionContext
    Handle(SelectionContext) myBaseContext;
    Handle(SelectionContext) myCurrentContext;

    std::vector<Handle(SelectionContext)> mySelectionContexts;

    bool myContextUpdatePending;
};

#endif // !SelectionManager_H
