#ifndef _LiveAction_h
#define _LiveAction_h

#include <vector>

#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>

#include "Iact/Framework/WorkspaceControl.h"

class WorkspaceControllr;

DEFINE_STANDARD_HANDLE(LiveAction, WorkspaceControl)

class LiveAction : public WorkspaceControl
{
public:
	explicit LiveAction() {}

private:
	bool myIsFinished;
};

#endif // !_LiveAction_h
