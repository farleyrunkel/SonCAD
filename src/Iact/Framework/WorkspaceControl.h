#ifndef _WorkspaceControl_h
#define _WorkspaceControl_h

#include <memory>
#include <vector>

 
 

#include "Comm/BaseObject.h"
#include "Iact/HudElements/HudElement.h"
#include "Iact/Panels/PropertyPanels/PropertyPanel.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/Snapping/SnapBase.h"

class WorkspaceController;

class WorkspaceControl : public BaseObject
{
public:
	explicit WorkspaceControl() {}

private:
	std::shared_ptr<WorkspaceController> myWorkspaceController;
	bool myPanelsHidden;
	bool myCleanedUp;
	std::vector<std::shared_ptr<HudElement>> myHudElements;
	std::vector<std::shared_ptr<VisualObject>> myVisualObjects;

	std::vector<std::shared_ptr<PropertyPanel>> myPanels;

	std::shared_ptr<SnapBase> mySnap;
};

#endif // !_WorkspaceControl_h
