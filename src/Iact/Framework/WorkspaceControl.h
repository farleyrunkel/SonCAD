#ifndef _WorkspaceControl_h
#define _WorkspaceControl_h

#include <Standard_Transient.hxx>

#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/WorkspaceController.h"

class WorkspaceControl : public Standard_Transient
{
public:
	explicit WorkspaceControl() {}

private:
	Handle(WorkspaceController) myWorkspaceController;
	bool myPanelsHidden;
	bool myCleanedUp;
	NCollection_Vector<Handle(VisualObject)> myVisualObjects;
};

#endif // !_WorkspaceControl_h
