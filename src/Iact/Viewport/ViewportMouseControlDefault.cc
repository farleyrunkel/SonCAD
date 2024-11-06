// Copyright [2024] SunCAD

#include "Iact/Viewport/ViewportMouseControlDefault.h"
#include <QMessageBox>
ViewportMouseControlDefault::ViewportMouseControlDefault() : viewportController(nullptr), 
    currentMouseMoveMode(ViewportController::MouseMoveMode::None) {}

void ViewportMouseControlDefault::setViewportController(ViewportController* controller) {
    viewportController = controller;
}

void ViewportMouseControlDefault::mouseDown(const QPointF& pos, Qt::MouseButton changedButton, int clickCount, QMouseEvent*, Qt::KeyboardModifiers modifierKeys) {
    if (!viewportController) return;

    if (changedButton == Qt::LeftButton) {
        if (clickCount == 2) {
            viewportController->startEditing();
        }
        else {
            viewportController->mouseDown(modifierKeys);
        }
    }

    mouseDownPos = pos;
    updateMouseMoveMode(nullptr, modifierKeys);
}

void ViewportMouseControlDefault::updateMouseMoveMode(QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys) {
    if (mouseEvent && (mouseEvent->buttons() & Qt::MiddleButton)) {
        if (modifierKeys & Qt::ControlModifier) {
            currentMouseMoveMode = ViewportController::MouseMoveMode::Twisting;
        }
        else if (viewportController->isLockedToPlane()) {
            currentMouseMoveMode = ViewportController::MouseMoveMode::Panning;
        }
        else {
            currentMouseMoveMode = ViewportController::MouseMoveMode::Rotating;
        }
    }
    else if (mouseEvent && (mouseEvent->buttons() & Qt::RightButton)) {
        currentMouseMoveMode = (modifierKeys & Qt::ControlModifier) ?
            ViewportController::MouseMoveMode::Zooming : ViewportController::MouseMoveMode::Panning;
    }
    else {
        currentMouseMoveMode = ViewportController::MouseMoveMode::None;
    }
}

void ViewportMouseControlDefault::mouseMove(const QPointF& pos, QMouseEvent* mouseEvent, Qt::KeyboardModifiers modifierKeys) {
    if (!viewportController) return;

    if (currentMouseMoveMode != ViewportController::MouseMoveMode::None) {
        viewportController->mouseMove(pos, modifierKeys, currentMouseMoveMode);
    }
    else {
        if (mouseEvent->buttons() & Qt::LeftButton && (pos - mouseDownPos).manhattanLength() > 10
            && !viewportController->isInRubberbandSelection()
            && viewportController->workspaceController()->isSelecting()) {
            // viewportController->startRubberbandSelection(mouseDownPos);
        }

        viewportController->mouseMove(pos, modifierKeys);
    }
    updateMouseMoveMode(mouseEvent, modifierKeys);
}

void ViewportMouseControlDefault::mouseWheel(const QPointF& pos, MouseWheel wheel, int delta, QInputEvent*, Qt::KeyboardModifiers modifierKeys) {
    if (!viewportController || delta == 0) return;

    double scaledDelta = delta;
    if (modifierKeys & Qt::ControlModifier) {
        scaledDelta /= 10.0;
    }

    switch (wheel) {
    case MouseWheel::Vertical:
        viewportController->zoom(pos, scaledDelta / 200.0);
        break;
    case MouseWheel::Horizontal:
        viewportController->rotate(scaledDelta / -50.0, 0, 0);
        break;
    }
    viewportController->mouseMove(pos, modifierKeys);
}

void ViewportMouseControlDefault::mouseUp(const QPointF& pos, Qt::MouseButton changedButton, QMouseEvent*, Qt::KeyboardModifiers modifierKeys) {
    if (!viewportController) return;

    if (changedButton == Qt::LeftButton) {
        viewportController->mouseUp(modifierKeys);
    }
    updateMouseMoveMode(nullptr, modifierKeys);
}

void ViewportMouseControlDefault::cancel() {
    if (viewportController) {
        viewportController->mouseMove(QPointF(-1, -1), Qt::KeyboardModifier::NoModifier);
        currentMouseMoveMode = ViewportController::MouseMoveMode::None;
    }
}