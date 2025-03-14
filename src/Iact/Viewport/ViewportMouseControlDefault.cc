// Copyright [2024] SunCAD

#include "Iact/Viewport/ViewportMouseControlDefault.h"
#include <QMessageBox>



    ViewportMouseControlDefault::ViewportMouseControlDefault() :
        _ViewportController(nullptr),
        currentMouseMoveMode(ViewportController::MouseMoveMode::None) {
    }

    void ViewportMouseControlDefault::SetViewportController(const Handle(ViewportController)& controller) {
        _ViewportController = controller;
    }

    void ViewportMouseControlDefault::MouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys) {
        //qDebug() << "ViewportMouseControlDefault::MouseMove: " << pos;

        //if (!myViewportController) return;

        //if (currentMouseMoveMode != ViewportController::MouseMoveMode::None) {
        //    myViewportController->MouseMove(pos, modifierKeys, currentMouseMoveMode);
        //}
        //else {
        //    if (mouseEvent->buttons() & Qt::LeftButton && (pos - mouseDownPos).manhattanLength() > 10
        //        //&& !myViewportController->IsInRubberbandSelection()
        //        //&& myViewportController->GetWorkspaceController()->IsSelecting()) {
        //        // myViewportController->startRubberbandSelection(mouseDownPos);
        //    }

        //    myViewportController->MouseMove(pos, modifierKeys);
        //}
        //updateMouseMoveMode(mouseEvent, modifierKeys);
    }

    void ViewportMouseControlDefault::MouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent*, Qt::KeyboardModifiers ModifierKeys) {
        //if (myViewportController->IsNull()) return;

        //if (changedButton == Qt::LeftButton) {
        //    if (clickCount == 2) {
        //        myViewportController->StartEditing();
        //    }
        //    else {
        //        myViewportController->MouseDown(modifierKeys);
        //    }
        //}

        //mouseDownPos = pos;
        //updateMouseMoveMode(nullptr, modifierKeys);
    }

    void ViewportMouseControlDefault::MouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent*, Qt::KeyboardModifiers ModifierKeys) {
        if (!_ViewportController) return;

        if (changedButton == Qt::LeftButton) {
            _ViewportController->MouseUp(ModifierKeys);
        }
        updateMouseMoveMode(nullptr, ModifierKeys);
    }

    void ViewportMouseControlDefault::updateMouseMoveMode(QMouseEvent* mouseEvent, Qt::KeyboardModifiers ModifierKeys) {
        //if (mouseEvent && (mouseEvent->buttons() & Qt::MiddleButton)) {
        //    if (modifierKeys & Qt::ControlModifier) {
        //        currentMouseMoveMode = Sun__ViewportController::MouseMoveMode::Twisting;
        //    }
        //    else if (myViewportController->IsLockedToPlane()) {
        //        currentMouseMoveMode = Sun__ViewportController::MouseMoveMode::Panning;
        //    }
        //    else {
        //        currentMouseMoveMode = Sun__ViewportController::MouseMoveMode::Rotating;
        //    }
        //}
        //else if (mouseEvent && (mouseEvent->buttons() & Qt::RightButton)) {
        //    currentMouseMoveMode = (modifierKeys & Qt::ControlModifier) ?
        //        Sun__ViewportController::MouseMoveMode::Zooming : Sun__ViewportController::MouseMoveMode::Panning;
        //}
        //else {
        //    currentMouseMoveMode = Sun__ViewportController::MouseMoveMode::None;
        //}
    }

    void ViewportMouseControlDefault::MouseWheel(const QPointF& pos, MouseWheelEnum wheel, int delta, QInputEvent*, Qt::KeyboardModifiers ModifierKeys) {
        //if (!myViewportController || delta == 0) return;

        //double scaledDelta = delta;
        //if (modifierKeys & Qt::ControlModifier) {
        //    scaledDelta /= 10.0;
        //}

        //switch (wheel) {
        //case MouseWheel::Vertical:
        //myViewportController->Zoom(pos, scaledDelta / 200.0);
        //break;
        //case MouseWheel::Horizontal:
        //myViewportController->Rotate(scaledDelta / -50.0, 0, 0);
        //break;
        //}
        //myViewportController->MouseMove(pos, modifierKeys);
    }

    void ViewportMouseControlDefault::Cancel() {
        //if (myViewportController) {
        //    myViewportController->MouseMove(QPointF(-1, -1), Qt::KeyboardModifier::NoModifier);
        //    currentMouseMoveMode = Sun__ViewportController::MouseMoveMode::None;
        //}
    }
