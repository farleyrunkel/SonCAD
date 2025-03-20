#ifndef IACT_WORKSPACE_SELECTION_SelectionContext_H_
#define IACT_WORKSPACE_SELECTION_SelectionContext_H_

#include <NCollection_Vector.hxx>

#include "Comm/BaseObject.h"
#include "Core/Topology/InteractiveEntity.h"

class WorkspaceController;

DEFINE_STANDARD_HANDLE(SelectionContext, BaseObject)

class SelectionContext : public BaseObject
{
public:
    enum Option
    {
        None = 0,
        IncludeAll = 1 << 0,
        NewSelectedList = 1 << 1,
    };
    typedef Standard_Integer Options;

public:
	SelectionContext(const Handle(WorkspaceController)& workspaceController, Options options)
	{
		_WorkspaceController = workspaceController;
		_Options = options;
		if(_Options & NewSelectedList)
		{
			SelectedEntities.Clear();
		}
    }

	void Include(const Handle(InteractiveEntity)& entity)
	{
		//auto visShape = _WorkspaceController->visualObject(entity);
	}

private:
    NCollection_Vector<Handle(InteractiveEntity)> SelectedEntities;
	Handle(WorkspaceController) _WorkspaceController;

	Options _Options;
};

#endif // !IACT_WORKSPACE_SELECTION_SelectionContext_H_
