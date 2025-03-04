#ifndef SelectionContext_H
#define SelectionContext_H

#include <set>
#include <vector>

 
#include <SelectMgr_Filter.hxx>

#include "Core/Framework/OcctUtils/SubshapeType.h"
#include "Core/Topology/InteractiveEntity.h"
#include "Iact/Visual/VisualObject.h"
#include "Comm/BaseObject.h"

class WorkspaceController;

class SelectionContext : public enable_property_changed_signal
{
public:
    enum Options
    {
        None = 0,
        IncludeAll = 1 << 0,
        NewSelectedList = 1 << 1,
    };

public:
	SelectionContext() {}

private:
	std::vector<std::shared_ptr<InteractiveEntity>> mySelectedEntities;
	std::shared_ptr<WorkspaceController> myWorkspaceController;
    
	std::set<std::shared_ptr<VisualObject>> myVisualObjects;
	Options myOptions;

    bool myIsActive;
	SubshapeTypes mySubshapeType;
	Handle(SelectMgr_Filter) myFilter;
};

#endif // !SelectionContext_H
