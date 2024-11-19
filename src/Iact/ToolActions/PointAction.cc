// Copyright [2024] SunCAD

#include "Iact/ToolActions/PointAction.h"

#include <ProjLib.hxx>

#include "Iact/Workspace/WorkspaceController.h"

PointAction::PointAction() 
    : ToolAction(),
      _IsFinished(false),
      _Marker(nullptr){
    qDebug() << "Debug: PointAction::PointAction";
}

bool PointAction::onStart() {
    // QMessageBox::warning(nullptr, "adsd", "dasds");
    qDebug() << "Debug: PointAction::OnStart";

    return true;
}

bool PointAction::onMouseMove(const std::shared_ptr<MouseEventData>& data) {
    qDebug() << "Debug: PointAction::onMouseMove";
    if (!_IsFinished) {
        _EnsureMarker();
        ProcessMouseInput(data);
        auto args = std::make_shared<EventArgs>(
            _CurrentPoint,
            ProjLib::Project(workspaceController()->workspace()->workingPlane(), _CurrentPoint),
            _CurrentPoint,
            data
        );

        emit Preview(args);
        _Marker->Set(args->Point);
        workspaceController()->Invalidate();
        return ToolAction::onMouseMove(data);
    }

    return false;
}

bool PointAction::onMouseDown(const std::shared_ptr<MouseEventData>& data) { 
    return false; 
}

bool PointAction::onMouseUp(const std::shared_ptr<MouseEventData>& data) {
    if (!_IsFinished) {
        
        ProcessMouseInput(data);
        _IsFinished = true;
        auto args = std::make_shared<EventArgs>(
            _CurrentPoint,
            ProjLib::Project(workspaceController()->workspace()->workingPlane(), _CurrentPoint),
            _CurrentPoint,
            data
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

void PointAction::ProcessMouseInput(const std::shared_ptr<MouseEventData>& data) {
    qDebug() << "Debug: PointAction::ProcessMouseInput";


    {
        _CurrentPoint = data->PointOnPlane;
        //Remove(_HintLine);
    }
}
