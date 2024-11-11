// Copyright [2024] SunCAD

#include "Iact/ToolActions/PointAction.h"

#include "Iact/Workspace/WorkspaceController.h"

PointAction::PointAction() 
    : ToolAction(), m_isFinished(false) {
    qDebug() << "Debug: PointAction::PointAction";
}

bool PointAction::onStart() {
    // QMessageBox::warning(nullptr, "adsd", "dasds");
    qDebug() << "Debug: PointAction::onStart";

    return true;
}

bool PointAction::onMouseMove(MouseEventData* data) {
    qDebug() << "Debug: PointAction::onMouseMove";
    if (!m_isFinished) {
        ensureMarker();
        processMouseInput(data);
        EventArgs* args = new EventArgs(
        );

        emit preview(args);
        workspaceController()->invalidate();
        return ToolAction::onMouseMove(data);
    }

    return false;
}

bool PointAction::onMouseDown(MouseEventData* data) { 
    return false; }

bool PointAction::onMouseUp(MouseEventData* data) {
    if (!m_isFinished) {
        
        processMouseInput(data);
        m_isFinished = true;
        EventArgs* args = new EventArgs(
        );

        emit finished(args);
    }
    return false; }

void PointAction::ensureMarker() {
    if (_Marker == nullptr) {
        _Marker = new Marker(workspaceController(), Marker::Styles::Bitmap, Marker::PlusImage);
        // Add(_Marker);
    }
}

void PointAction::processMouseInput(MouseEventData* data) {
    qDebug() << "Debug: PointAction::processMouseInput";
}
