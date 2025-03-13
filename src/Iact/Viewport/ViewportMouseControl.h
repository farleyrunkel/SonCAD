// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_ViewportMouseControl_H_
#define IACT_VIEWPORT_ViewportMouseControl_H_

#include <QPointF>
#include <QMouseEvent>
#include <QInputEvent>

#include "Iact/Workspace/ViewportController.h"

// Interface for viewport mouse control
class ViewportMouseControl
{
public:
    // Enum to represent mouse wheel direction
    enum class MouseWheel
    {
        Vertical,
        Horizontal
    };
public:
    ViewportMouseControl() = default;
    virtual ~ViewportMouseControl() = default;

    // Set the viewport controller
    virtual void setViewportController(const std::shared_ptr<ViewportController>& controller) { m_viewportController = controller; }

    // Handle mouse move event
    virtual void MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys) = 0;

    // Handle mouse wheel event
    virtual void mouseWheel(const QPointF& pos, MouseWheel wheel, int delta, QInputEvent* device, Qt::KeyboardModifiers modifierKeys) = 0;

    // Handle mouse down event
    virtual void MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifierKeys) = 0;

    // Handle mouse up event
    virtual void MouseUp(const QPointF& pos, Qt::MouseButton changedButton, Qt::MouseButtons device, Qt::KeyboardModifiers modifierKeys) = 0;

    // Cancel any ongoing operation
    virtual void cancel() = 0;

protected:
	// Get the viewport controller
	std::shared_ptr<ViewportController> viewportController() const { return m_viewportController; }

private:
    std::shared_ptr<ViewportController> m_viewportController;
};

#endif  // IACT_VIEWPORT_ViewportMouseControl_H_
