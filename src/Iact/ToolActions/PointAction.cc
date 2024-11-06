// Copyright [2024] SunCAD

#include "Iact/ToolActions/PointAction.h"

#include "Iact/Workspace/WorkspaceController.h"

PointAction::PointAction() :
    m_isFinished(false) {
}

bool PointAction::onStart() {
    QMessageBox::warning(nullptr, "adsd", "dasds");

    return false;
}

bool PointAction::onMouseMove(MouseEventData* data) {
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

void PointAction::processMouseInput(MouseEventData* data) {

}
