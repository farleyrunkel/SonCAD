#ifndef _Editor_h
#define _Editor_h

#include <vector>

 
 

#include "Iact/Framework/WorkspaceControl.h"

class WorkspaceControllr;


class Editor : public WorkspaceControl
{
public:
	explicit Editor() {}

private:
	bool myIsFinished;
};

#endif // !_Editor_h
