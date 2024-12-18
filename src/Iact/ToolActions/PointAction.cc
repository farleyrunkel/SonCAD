// Copyright [2024] SunCAD

#include "Iact/ToolActions/PointAction.h"

#include <ProjLib.hxx>

#include "Iact/Workspace/WorkspaceController.h"

PointAction::PointAction() 
    : ToolAction(),
      _Marker(nullptr){
    qDebug() << "Debug: PointAction::PointAction";
}

bool PointAction::onStart() 
{
    qDebug() << "Debug: PointAction::OnStart";
    return true;
}

bool PointAction::onMouseMove(MouseEventData* data) {
    qDebug() << "- PointAction::onMouseMove";
    if (!_IsFinished) {
        _EnsureMarker();
        ProcessMouseInput(data);
        auto workingPlane = WorkspaceController()->Sun_Workspace()->WorkingPlane();

        EventArgs* args = new EventArgs(
            _CurrentPoint,
            ProjLib::Project(workingPlane, _CurrentPoint),
            _CurrentPoint,
            data
        );

        emit Preview(args);

        _Marker->Set(args->Point);
        WorkspaceController()->Invalidate();
        return ToolAction::onMouseMove(data);
    }

    return false;
}

bool PointAction::onMouseDown(MouseEventData* data) { 
    return false; 
}

bool PointAction::onMouseUp(MouseEventData* data) {
    if (!_IsFinished) {
        
        ProcessMouseInput(data);
        _IsFinished = true;
        auto args = new EventArgs(
            _CurrentPoint,
            ProjLib::Project(WorkspaceController()->Sun_Workspace()->WorkingPlane(), _CurrentPoint),
            _CurrentPoint,
            data
        );

        emit Finished(args);
    }
    return false; 
}

void PointAction::_EnsureMarker() {
    if (_Marker == nullptr) {
        _Marker = new Marker(WorkspaceController(), Marker::Styles::Bitmap, Marker::PlusImage());
        Add(_Marker);
    }
}

void PointAction::ProcessMouseInput(MouseEventData* data) {
    qDebug() << "Debug: PointAction::ProcessMouseInput";
    {
        _CurrentPoint = data->PointOnPlane;
        //Remove(_HintLine);
    }
}
