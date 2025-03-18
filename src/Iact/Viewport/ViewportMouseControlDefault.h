// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_
#define IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_

#include <QPointF>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QScopedPointer>

#include <Graphic3d_Vec2.hxx>
#include <Aspect_VKeyFlags.hxx>

#include "Iact/Viewport/ViewportMouseControl.h"
#include "Iact/Workspace/ViewportController.h"

class ViewportMouseControlDefault : public ViewportMouseControl
{
public:
    explicit ViewportMouseControlDefault();

    virtual void SetViewportController(const Handle(ViewportController)& controller) override;

    virtual void MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys) override;

    virtual void MouseMove(const Graphic3d_Vec2d& pos, Aspect_VKeyMouse buttons, Aspect_VKeyFlags keys) override;

    virtual void MouseWheel(const QPointF& pos, MouseWheelEnum wheel, int delta, QInputEvent* device, Qt::KeyboardModifiers ModifierKeys) override;

    virtual void MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent* /*mouseEvent*/, Qt::KeyboardModifiers ModifierKeys) override;

    virtual void MouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent* /*mouseEvent*/, Qt::KeyboardModifiers ModifierKeys) override;

    virtual void Cancel() override;

private:
    void updateMouseMoveMode(QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys);

private:
    ViewportController::MouseMoveMode currentMouseMoveMode;
    QPointF mouseDownPos;
};

#endif  // IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_
