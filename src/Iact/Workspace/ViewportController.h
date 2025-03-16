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

	void SetViewCube(bool isVisible);

	void SetViewCube(bool isVisible, int size, double duration);

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
		return myViewport;
	}

	Handle(WorkspaceController) GetWorkspaceController()
	{
		return _WorkspaceController;
	}

	void InitWindow();

	void SetPredefinedView(PredefinedViews predefinedView);

	void ZoomFitAll();
	
	void Zoom(double value);

public:
	void MouseMove(const QPointF& pos, Qt::KeyboardModifiers modifiers,
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
	void Zoom(const QPointF& pos, double delta)
	{}

	void Rotate(double deltaX, double deltaY, double deltaZ)
	{}
private:
	void Init()
	{
		myViewport->Init(true);
	}

	void _UpdateParameter();

private:
	Handle(Viewport) myViewport;
	Handle(WorkspaceController)  _WorkspaceController;

	Handle(AIS_ViewCube) _ViewCube;
};

#endif  // IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
