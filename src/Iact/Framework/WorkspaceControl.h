#ifndef _WorkspaceControl_h
#define _WorkspaceControl_h

#include <vector>

#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>

#include "Iact/HudElements/HudElement.h"
#include "Iact/Panels/PropertyPanels/PropertyPanel.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/Snapping/SnapBase.h"

class WorkspaceController;

DEFINE_STANDARD_HANDLE(WorkspaceControl, Standard_Transient)

class WorkspaceControl : public Standard_Transient
{
public:
	explicit WorkspaceControl() {}

private:
	Handle(WorkspaceController) myWorkspaceController;
	bool myPanelsHidden;
	bool myCleanedUp;
	std::vector<std::shared_ptr<HudElement>> myHudElements;
	std::vector<Handle(VisualObject)> myVisualObjects;

	std::vector<std::shared_ptr<PropertyPanel>> myPanels;

	Handle(SnapBase) mySnap;
};

#endif // !_WorkspaceControl_h
