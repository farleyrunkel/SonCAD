#ifndef SelectionContext_H
#define SelectionContext_H

#include <set>
#include <vector>

#include <Standard_Transient.hxx>
#include <SelectMgr_Filter.hxx>

#include "Core/Framework/OcctUtils/SubshapeType.h"
#include "Core/Topology/InteractiveEntity.h"
#include "Iact/Visual/VisualObject.h"

class WorkspaceController;

DEFINE_STANDARD_HANDLE(SelectionContext, Standard_Transient)

class SelectionContext : public Standard_Transient
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
	std::vector<Handle(InteractiveEntity)> mySelectedEntities;
	Handle(WorkspaceController) myWorkspaceController;
    
	std::set<Handle(VisualObject)> myVisualObjects;
	Options myOptions;

    bool myIsActive;
	SubshapeTypes mySubshapeType;
	Handle(SelectMgr_Filter) myFilter;
};

#endif // !SelectionContext_H
