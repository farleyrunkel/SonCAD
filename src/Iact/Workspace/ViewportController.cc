
#include "Iact/Workspace/ViewportController.h"

#include <cmath>

#include <AIS_RubberBand.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <NCollection_Vec2.hxx>
#include <NCollection_Vector.hxx>
#include <Aspect_RenderingContext.hxx>
#include <Aspect_Window.hxx>

#include <WNT_WClass.hxx>
#include <WNT_Window.hxx>

#include "Core/Project/Viewport.h"
#include "Core/Project/Workspace.h"
#include "Occt/OcctExtensions/AIS_ViewCubeEx.h"

ViewportController::ViewportController(const std::shared_ptr<Viewport>& viewport, const std::shared_ptr<WorkspaceController>& WC)
	: myViewport(viewport)
	, myWorkspaceController(WC)
	, _LockedToPlane(false)
	, _ShowTrihedron(false)
	, _RubberbandIncludeTouched(false)
	, IsInRubberbandSelection(false)
	, myRubberbandSelectionMode(RubberbandSelectionMode::Rectangle)
	, _ZoomFitAllOnInit(false)
{
	init();
}

std::shared_ptr<Viewport> ViewportController::viewport() const
{
	return myViewport;
}

void ViewportController::init()
{
	viewport()->init(true);
}

Handle(Aspect_Window) ViewportController::window() const
{
	return !view().IsNull() ? view()->Window() : nullptr;
}

void ViewportController::SetWindow(const Handle(Aspect_Window)& theWindow, const Aspect_RenderingContext theContext)
{
	if(!view().IsNull())
	{
		view()->SetWindow(theWindow, theContext);
	}
}

Handle(AIS_ViewCube) ViewportController::viewCube() const
{
	return myViewCube;
}

