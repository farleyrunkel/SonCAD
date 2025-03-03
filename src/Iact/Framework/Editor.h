#ifndef _Editor_h
#define _Editor_h

#include <vector>

#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>

#include "Iact/Framework/WorkspaceControl.h"

class WorkspaceControllr;

DEFINE_STANDARD_HANDLE(Editor, WorkspaceControl)

class Editor : public WorkspaceControl
{
public:
	explicit Editor() {}

private:
	bool myIsFinished;
};

#endif // !_Editor_h
