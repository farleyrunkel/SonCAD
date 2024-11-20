// Copyright [2024] SunCAD

#ifndef SRC_IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_
#define SRC_IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_

#include <QPointF>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QScopedPointer>

#include "Iact/Viewport/IViewportMouseControl.h"
#include "Iact/Workspace/ViewportController.h"

class ViewportMouseControlDefault : public IViewportMouseControl {
 public:
    explicit ViewportMouseControlDefault();

    void setViewportController(Sun_ViewportController* controller) override;

    void mouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys) override;

    void mouseWheel(const QPointF& pos, MouseWheel wheel, int delta, QInputEvent* /*device*/, Qt::KeyboardModifiers modifierKeys) override;

    void mouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent* /*mouseEvent*/, Qt::KeyboardModifiers modifierKeys) override;

    void mouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent* /*mouseEvent*/, Qt::KeyboardModifiers modifierKeys) override;

    void cancel() override;

 private:
    void updateMouseMoveMode(QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys);
 
 private:
    Sun_ViewportController* viewportController;
    Sun_ViewportController::MouseMoveMode currentMouseMoveMode;
    QPointF mouseDownPos;
};
 
#endif  // SRC_IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_
