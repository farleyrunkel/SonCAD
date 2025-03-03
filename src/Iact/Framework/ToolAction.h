#ifndef _ToolAction_h
#define _ToolAction_h

#include <vector>

#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>

#include "Iact/Framework/WorkspaceControl.h"

class WorkspaceControllr;

DEFINE_STANDARD_HANDLE(ToolAction, WorkspaceControl)

class ToolAction : public WorkspaceControl
{
public:
	explicit ToolAction() {}

private:
	bool myIsFinished;
};

#endif // !_ToolAction_h
