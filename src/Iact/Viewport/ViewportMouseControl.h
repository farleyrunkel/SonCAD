// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_
#define IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_

#include <QPointF>
#include <QMouseEvent>
#include <QInputEvent>

#include <Graphic3d_Vec2.hxx>
#include <Aspect_VKeyFlags.hxx>

#include "Iact/Workspace/ViewportController.h"

    // Interface for viewport mouse control
class ViewportMouseControl
{
public:
    // Enum to represent mouse wheel direction
    enum MouseWheelEnum
    {
        Vertical,
        Horizontal
    };

public:
    ViewportMouseControl() = default;
    virtual ~ViewportMouseControl() = default;

    // Set the viewport controller
    virtual void SetViewportController(const Handle(ViewportController)& controller) { _ViewportController = controller; }

    // Handle mouse move event
    virtual void MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys) = 0;

    virtual void MouseMove(const Graphic3d_Vec2d& pos, Aspect_VKeyMouse buttons, Aspect_VKeyFlags keys) {}

    // Handle mouse wheel event
    virtual void MouseWheel(const QPointF& pos, MouseWheelEnum wheel, int delta, QInputEvent* device, Qt::KeyboardModifiers ModifierKeys) = 0;

    // Handle mouse down event
    virtual void MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys) = 0;

    // Handle mouse up event
    virtual void MouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys) = 0;

    // Cancel any ongoing operation
    virtual void Cancel() = 0;

protected:
    Handle(ViewportController) _ViewportController;
};


#endif  // IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_
