// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

#include <QObject>

#include "Comm/BaseObject.h"
#include "Core/Viewport.h"
#include "Occt/OcctExtensions/AIS_ViewCubeEx.h"

class WorkspaceController;

DEFINE_STANDARD_HANDLE(ViewportController, BaseObject)

class ViewportController : public BaseObject
{
public:
	ViewportController(const Handle(Viewport)& viewport, const Handle(WorkspaceController)& wc);

	// get viewcube
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

	Handle(Viewport) GetViewport()
	{
		return _Viewport;
	}

	Handle(WorkspaceController) GetWorkspaceController()
	{
		return _WorkspaceController;
	}

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

	void _SetTrihedron(bool visible);

public:
	void MouseMove(const Graphic3d_Vec2d& pos, 
				   Aspect_VKeyFlags keys, 
				   MouseMoveMode mode = MouseMoveMode::None)
	{};
	void MouseDown(Qt::KeyboardModifiers modifiers)
	{};
	void MouseUp(Qt::KeyboardModifiers modifiers)
	{};
	void StartEditing()
	{}
	void StartRubberbandSelection()
	{}  // Add necessary parameters

private:
	void Init()
	{
		_Viewport->Init(true);
	}

	void _UpdateParameter();


	void _SetMouseMoveMode(MouseMoveMode mode);


	void _ResetMouseMoveMode()
	{
		_GravityPoint = gp_Pnt(0, 0, 0);
		_CurrentMouseMoveMode = MouseMoveMode::None;
	}

	void _SetViewCube(bool isVisible);

	void _SetViewCube(bool isVisible, int size, double duration);

private:
	Handle(Viewport) _Viewport;
	Handle(WorkspaceController)  _WorkspaceController;

	Handle(AIS_ViewCube) _ViewCube;

	gp_Pnt  _GravityPoint;
	Graphic3d_Vec2d _StartedMousePosition;
	Graphic3d_Vec2d _LastMousePosition;

	MouseMoveMode _CurrentMouseMoveMode;

	bool _LockedToPlane;
};

#endif  // IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
