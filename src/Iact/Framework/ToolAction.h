#ifndef _ToolAction_h
#define _ToolAction_h

#include <vector>

 
 

#include "Iact/Framework/WorkspaceControl.h"

class WorkspaceControllr;

class ToolAction : public WorkspaceControl
{
public:
	explicit ToolAction() {}

private:
	bool myIsFinished;
};

#endif // !_ToolAction_h
