#ifndef _WorkspaceController_h
#define _WorkspaceController_h

#include <chrono>
#include <thread>
#include <vector>

#include <AIS_InteractiveObject.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
 

#include "Comm/BaseObject.h"
#include "Core/Project/Viewport.h"
#include "Core/Project/Workspace.h"
#include "Iact/HudElements/HudManager.h"
#include "Iact/Visual/VisualObjectManager.h"
#include "Iact/Workspace/Selection/SelectionManager.h"
#include "Iact/Workspace/ViewportController.h"
#include "Occt/AisExtensions/AISX_Grid.h"

class WorkspaceController : public BaseObject
{
public:
	explicit WorkspaceController() {}

private:
	std::shared_ptr<Workspace> myWorkspace;
	std::shared_ptr<Viewport> myActiveViewport;

	std::shared_ptr<SelectionManager> mySelectionManager;
	std::shared_ptr<VisualObjectManager> myVisualObjectManager;
	std::shared_ptr<HudManager> myHudManager;

	bool myLockWorkingPlane;
	bool myIsSelecting;
	gp_Pnt myCursorPosition;
	gp_Pnt2d myCursorPosition2d;

	std::vector<std::shared_ptr<ViewportController>> myViewports;
	std::thread myRedrawTimer;

	Handle(AISX_Grid) myGrid;
	gp_XY myLastGridSize;
	bool myGridNeedsUpdate;
	std::vector<Handle(AIS_InteractiveObject)> myObjects;
 };

#endif // !_WorkspaceController_h
