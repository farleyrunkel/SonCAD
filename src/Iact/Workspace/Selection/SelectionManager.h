#ifndef SelectionManager_H
#define SelectionManager_H

#include <vector>

 

#include "Core/Topology/InteractiveEntity.h"
#include "Iact/Workspace/Selection/SelectionContext.h"
#include "Comm/BaseObject.h"

class WorkspaceController;

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
    SelectionManager() {}

private:
    std::vector<std::shared_ptr<InteractiveEntity>> myEmptyList;

    std::shared_ptr<WorkspaceController> myWorkspaceController;

    // SelectionContext
    std::shared_ptr<SelectionContext> myBaseContext;
    std::shared_ptr<SelectionContext> myCurrentContext;

    std::vector<std::shared_ptr<SelectionContext>> mySelectionContexts;

    bool myContextUpdatePending;
};

#endif // !SelectionManager_H
