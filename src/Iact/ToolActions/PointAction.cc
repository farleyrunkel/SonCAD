// Copyright [2024] SunCAD

#include "Iact/ToolActions/PointAction.h"

#include <ProjLib.hxx>

#include "Iact/Workspace/WorkspaceController.h"

PointAction::PointAction() 
    : ToolAction(),
      m_isFinished(false),
      _Marker(nullptr){
    qDebug() << "Debug: PointAction::PointAction";
}

bool PointAction::onStart() {
    // QMessageBox::warning(nullptr, "adsd", "dasds");
    qDebug() << "Debug: PointAction::OnStart";

    return true;
}

bool PointAction::onMouseMove(MouseEventData* data) {
    qDebug() << "Debug: PointAction::onMouseMove";
    if (!m_isFinished) {
        _EnsureMarker();
        processMouseInput(data);
        EventArgs* args = new EventArgs(
            _CurrentPoint,
            ProjLib::Project(workspaceController()->workspace()->workingPlane(), _CurrentPoint),
            _CurrentPoint,
            data
        );

        emit Preview(args);
        workspaceController()->Invalidate();
        return ToolAction::onMouseMove(data);
    }

    return false;
}

bool PointAction::onMouseDown(MouseEventData* data) { 
    return false; 
}

bool PointAction::onMouseUp(MouseEventData* data) {
    if (!m_isFinished) {
        
        processMouseInput(data);
        m_isFinished = true;
        EventArgs* args = new EventArgs(
        );

        emit Finished(args);
    }
    return false; 
}

void PointAction::_EnsureMarker() {
    if (_Marker == nullptr) {
        _Marker = new Marker(workspaceController(), Marker::Styles::Bitmap, Marker::PlusImage());
        Add(_Marker);
    }
}

void PointAction::processMouseInput(MouseEventData* data) {
    qDebug() << "Debug: PointAction::processMouseInput";
}
