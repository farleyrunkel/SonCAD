// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_
#define IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_

#include <QPointF>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QScopedPointer>

#include "Iact/Viewport/ViewportMouseControl.h"
#include "Iact/Workspace/ViewportController.h"

    class ViewportMouseControlDefault : public ViewportMouseControl
    {
    public:
        explicit ViewportMouseControlDefault();

        virtual void SetViewportController(const Handle(ViewportController)& controller) override;

        virtual void MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys) override;

        virtual void MouseWheel(const QPointF& pos, MouseWheelEnum wheel, int delta, QInputEvent* device, Qt::KeyboardModifiers ModifierKeys) override;

        virtual void MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent* /*mouseEvent*/, Qt::KeyboardModifiers ModifierKeys) override;

        virtual void MouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent* /*mouseEvent*/, Qt::KeyboardModifiers ModifierKeys) override;

        virtual void Cancel() override;

    private:
        void updateMouseMoveMode(QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys);

    private:
        Handle(ViewportController) _ViewportController;
        ViewportController::MouseMoveMode currentMouseMoveMode;
        QPointF mouseDownPos;
    };

#endif  // IACT_VIEWPORT_VIEWPORTMOUSECONTROLDEFAULT_H_
