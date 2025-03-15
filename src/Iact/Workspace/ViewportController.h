// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

#include <QObject>

#include "Comm/BaseObject.h"
#include "Core/Viewport.h"


DEFINE_STANDARD_HANDLE(ViewportController, BaseObject)

class ViewportController : public BaseObject
{
public:
	ViewportController()
	{
		myViewport = new Viewport();
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
		return myViewport;
	}

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
	Handle(Viewport) myViewport;
};


#endif  // IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
