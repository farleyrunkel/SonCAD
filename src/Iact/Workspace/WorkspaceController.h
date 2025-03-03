#ifndef _WorkspaceController_h
#define _WorkspaceController_h

#include <chrono>
#include <thread>
#include <vector>

#include <AIS_InteractiveObject.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <Standard_Transient.hxx>

#include "Core/Project/Viewport.h"
#include "Core/Project/Workspace.h"
#include "Iact/HudElements/HudManager.h"
#include "Iact/Visual/VisualObjectManager.h"
#include "Iact/Workspace/Selection/SelectionManager.h"
#include "Iact/Workspace/ViewportController.h"
#include "Occt/AisExtensions/AISX_Grid.h"

DEFINE_STANDARD_HANDLE(WorkspaceController, Standard_Transient)

class WorkspaceController : public Standard_Transient
{
public:
	explicit WorkspaceController() {}

private:
	Handle(Workspace) myWorkspace;
	Handle(Viewport) myActiveViewport;

	Handle(SelectionManager) mySelectionManager;
	Handle(VisualObjectManager) myVisualObjectManager;
	Handle(HudManager) myHudManager;

	bool myLockWorkingPlane;
	bool myIsSelecting;
	gp_Pnt myCursorPosition;
	gp_Pnt2d myCursorPosition2d;

	std::vector<Handle(ViewportController)> myViewports;
	std::thread myRedrawTimer;

	Handle(AISX_Grid) myGrid;
	gp_XY myLastGridSize;
	bool myGridNeedsUpdate;
	std::vector<Handle(AIS_InteractiveObject)> myObjects;

 };

#endif // !_WorkspaceController_h
