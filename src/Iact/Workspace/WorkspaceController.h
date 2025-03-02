#ifndef _WorkspaceController_h
#define _WorkspaceController_h

#include <atomic>
#include <chrono>
#include <thread>

#include <AIS_InteractiveObject.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <NCollection_Vector.hxx>
#include <Standard_Transient.hxx>

#include "Core/Project/Viewport.h"
#include "Core/Project/Workspace.h"
#include "Iact/Workspace/ViewportController.h"
#include "Occt/AisExtensions/AISX_Grid.h"

class WorkspaceController : public Standard_Transient
{
public:
	explicit WorkspaceController() {}

private:
	Handle(Workspace) myWorkspace;
	Handle(Viewport) myActiveViewport;

	bool myLockWorkingPlane;
	bool myIsSelecting;
	gp_Pnt myCursorPosition;
	gp_Pnt2d myCursorPosition2d;

	NCollection_Vector<ViewportController> myViewports;
	std::thread myRedrawTimer;

	Handle(AISX_Grid) myGrid;
	gp_XY myLastGridSize;
	bool myGridNeedsUpdate;
	NCollection_Allocator<Handle(AIS_InteractiveObject)> myObjects;
 };

#endif // !_WorkspaceController_h
