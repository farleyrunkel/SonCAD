// Copyright [2024] SunCAD

#ifndef SRC_IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_
#define SRC_IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_

#include <QPointF>
#include <QMouseEvent>
#include <QInputEvent>

#include "Iact/Workspace/ViewportController.h"

// Interface for viewport mouse control
class IViewportMouseControl {
 public:
    // Enum to represent mouse wheel direction
    enum class MouseWheel {
        Vertical,
        Horizontal
    };

    IViewportMouseControl() = default;
    virtual ~IViewportMouseControl() = default;

    // Set the viewport controller
    virtual void setViewportController(ViewportController* controller) { m_viewportController = controller; }

    // Handle mouse move event
    virtual void mouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys) = 0;

    // Handle mouse wheel event
    virtual void mouseWheel(const QPointF& pos, MouseWheel wheel, int delta, QInputEvent* device, Qt::KeyboardModifiers modifierKeys) = 0;

    // Handle mouse down event
    virtual void mouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys) = 0;

    // Handle mouse up event
    virtual void mouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys) = 0;

    // Cancel any ongoing operation
    virtual void cancel() = 0;

 private:
    ViewportController* m_viewportController;
};

#endif  // SRC_IACT_VIEWPORT_IVIEWPORTMOUSECONTROL_H_
