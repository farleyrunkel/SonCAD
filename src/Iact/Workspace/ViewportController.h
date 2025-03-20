// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

#include <QObject>

#include <AIS_RubberBand.hxx>
#include <AIS_ViewCube.hxx>
#include <Graphic3d_Vec4.hxx>

#include "Comm/BaseObject.h"
#include "Core/Viewport.h"
#include "Iact/Workspace/ViewportParameterSet.h"
#include "Occt/OcctExtensions/AIS_ViewCubeEx.h"

class WorkspaceController;

DEFINE_STANDARD_HANDLE(ViewportController, BaseObject)

class ViewportController : public BaseObject
{
public:
	ViewportController(const Handle(Viewport)& viewport, const Handle(WorkspaceController)& wc);

	// Get viewcube
	Handle(AIS_ViewCube) GetViewCube()
	{
		return _ViewCube;
	}

public:
	enum class PredefinedViews
	{
		Top,
		Bottom,
		Left,
		Right,
		Front,
		Back,
		WorkingPlane
	};

	enum MouseMoveMode
	{
		None, Panning, Rotating, Twisting, Zooming
	};

	enum RubberbandSelectionMode
	{
		Rectangle,
		Freehand
	};

public:
	Handle(Viewport) GetViewport();

	Handle(WorkspaceController) GetWorkspaceController();

	bool LockedToPlane() const;

	void SetLockedToPlane(bool value);

	void InitWindow();

	void SetPredefinedView(PredefinedViews predefinedView);

	void Rotate(double yawDeg, double pitchDeg, double rollDeg);

	void Pan(double dx, double dy);

	void Zoom(const Graphic3d_Vec2d& pos, double delta);

	void Zoom(double value);

	void ZoomFitAll();

	void ZoomFitSelected();

	bool IsInRubberbandSelection() const;

	void StartRubberbandSelection(RubberbandSelectionMode mode, 
								  bool includeTouched, 
								  const Graphic3d_Vec2d& position = {});

public:
	void MouseMove(const Graphic3d_Vec2d& pos, 
				   Aspect_VKeyFlags keys = Aspect_VKeyFlags_NONE,
				   MouseMoveMode mode = MouseMoveMode::None);
	void MouseMove(Aspect_VKeyFlags keys);

	void MouseDown(Aspect_VKeyFlags keys);

	void MouseUp(Aspect_VKeyFlags keys);

private:
	void Init();

	void _UpdateParameter();

	void _ViewportParameterSet_ParameterChanged(OverridableParameterSet* set, std::string key);

	void _SetMouseMoveMode(MouseMoveMode mode);

	void _ResetMouseMoveMode();

	void _SetViewCube(bool isVisible);
	void _SetViewCube(bool isVisible, int size, double duration);

	void _SetTrihedron(bool visible);

	void _UpdateRubberbandSelection();

	void _StopRubberbandSelection();

	Graphic3d_Vec4i _CalcRectangleSelectionPoints(bool bottomUp);

private:
	Handle(Viewport) _Viewport;
	Handle(WorkspaceController)  _WorkspaceController;

	Handle(AIS_ViewCube) _ViewCube;
	Handle(AIS_RubberBand) _AisRubberBand;

	gp_Pnt  _GravityPoint;
	Graphic3d_Vec2d _StartedMousePosition;
	Graphic3d_Vec2d _LastMousePosition;

	MouseMoveMode _CurrentMouseMoveMode;

	bool _LockedToPlane;
	bool _ShowTrihedron;
	bool _ZoomFitAllOnInit;

	const int RubberbandFreehandSelectionThresholdSquared = 100;
	RubberbandSelectionMode _RubberbandMode;
	std::vector<Graphic3d_Vec2i> _RubberbandPoints;
	bool _RubberbandIncludeTouched;
};

#endif  // IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
