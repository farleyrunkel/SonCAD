#ifndef _ViewportController_h
#define _ViewportController_h

#include <cmath>
#include <QWidget>
#include <boost/signals2.hpp>

#include <AIS_RubberBand.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <NCollection_Vec2.hxx>
#include <NCollection_Vector.hxx>
 
#include <WNT_WClass.hxx>
#include <WNT_Window.hxx>

#include "Core/Project/Viewport.h"
#include "Core/Project/Workspace.h"
#include "Occt/OcctExtensions/AIS_ViewCubeEx.h"

class WorkspaceController;

class ViewportController
{
public:
	enum RubberbandSelectionMode
	{
		Rectangle,
		Freehand
	};

	enum MouseMoveMode
	{
		None,
		Panning,
		Rotating,
		Twisting,
		Zooming
	};

	enum PredefinedViews
	{
		Top,
		Bottom,
		Left,
		Right,
		Front,
		Back,
		WorkingPlane
	};

public:
	ViewportController(const std::shared_ptr<Viewport>& viewport, const std::shared_ptr<WorkspaceController>& WC);

	Handle(V3d_View) view() const
	{
		return this->viewport() ? this->viewport()->view() : nullptr;
	}

	std::shared_ptr<Viewport> viewport() const;

	Handle(Aspect_Window) window() const;

	void SetWindow(const Handle(Aspect_Window)& theWindow, const Aspect_RenderingContext theContext);

	Handle(AIS_ViewCube) viewCube() const;

	// get myWorkspaceController
	std::shared_ptr<WorkspaceController> workspaceController() const
	{
		return myWorkspaceController;
	}

	void updateParameter()
	{
		setViewCube(true, 30, 1);
	}

	// Getter for lockedToPlane
	bool LockedToPlane() const
	{
		return _LockedToPlane;
	}

	// Setter for lockedToPlane
	void SetLockedToPlane(bool value);

	void zoomFitAll();

	void setWidget(QWidget* widget)
	{
		m_host = widget;
	}

private:

	void init();

	void setViewCube(bool isVisible);
	void setViewCube(bool isVisible, int size, double duration);

	void setPredefinedView(PredefinedViews predefinedView);

	void setTrihedron(bool visible)
	{}

	void update()
	{
		if(m_host)
			m_host->update();
	}

public:
	boost::signals2::signal<void(bool)> sig_LockedToPlaneChanged;

private:
	QWidget* m_host;

	const int RubberbandFreehandSelectionThresholdSquared = 100;

	static Handle(WNT_WClass) _OcWindowClass;
	const double _OrbitProjectionConstraint =  M_PI_2 - 0.000000000001;
	Handle(WNT_Window) _OcWindow;
	bool _ZoomFitAllOnInit;

	NCollection_Vector<NCollection_Vec2<int>> _RubberbandPoints;

	std::shared_ptr<Viewport> myViewport;
	std::shared_ptr<Workspace> myWorkspace;
	std::shared_ptr<WorkspaceController> myWorkspaceController;

	bool IsInRubberbandSelection;

	gp_Pnt2d _StartedMousePosition;
	gp_Pnt2d _LastMousePosition;
	gp_Pnt _GravityPoint;
	bool _LockedToPlane;
	bool _ShowTrihedron;

	Handle(AIS_RubberBand) myRubberBand;
	RubberbandSelectionMode myRubberbandSelectionMode;

	bool _RubberbandIncludeTouched;

	Handle(AIS_ViewCubeEx) m_viewCube;
};

#endif // !_ViewportController_h
