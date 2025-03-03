#ifndef _Tool_h
#define _Tool_h

#include <vector>

#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>

#include "Iact/Framework/WorkspaceControl.h"

class WorkspaceControllr;

DEFINE_STANDARD_HANDLE(Tool, WorkspaceControl)

class Tool : public WorkspaceControl
{
public:
	explicit Tool() {}

private:
	std::vector<Handle(Tool)> myActions;
	std::vector<Handle(InteractiveEntity)> myOverriddenVisualShapes;
};

#endif // !_Tool_h
