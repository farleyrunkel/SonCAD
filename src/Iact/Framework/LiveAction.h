#ifndef _LiveAction_h
#define _LiveAction_h

#include <vector>

 
 

#include "Iact/Framework/WorkspaceControl.h"

class WorkspaceControllr;


class LiveAction : public WorkspaceControl
{
public:
	explicit LiveAction() {}

private:
	bool myIsFinished;
};

#endif // !_LiveAction_h
