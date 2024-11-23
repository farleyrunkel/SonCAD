// Copyright [2024] SunCAD

#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/Workspace/WorkspaceController.h"

CreateBoxTool::CreateBoxTool() 
	: Tool(),
	_Coord2DHudElement(nullptr) {
	
}

bool CreateBoxTool::OnStart() {
	qDebug() << "Debug: CreateBoxTool::OnStart";
	_CurrentPhase = Phase::PivotPoint;
	auto pointAction = new PointAction();
	if (!StartAction(pointAction)) {
		return false;
	}

	connect(pointAction, &PointAction::Preview, this, &CreateBoxTool::_PivotAction_Preview);
	connect(pointAction, &PointAction::Finished, this, &CreateBoxTool::_PivotAction_Finished);

	SetHintMessage("Select corner point.");
	_Coord2DHudElement = new Coord2DHudElement;
	Add(_Coord2DHudElement);
	return true;
}

void CreateBoxTool::_PivotAction_Preview(PointAction::EventArgs* args) {
	qDebug() << "Debug: CreateBoxTool::_PivotAction_Preview";
	if (_Coord2DHudElement) {
		_Coord2DHudElement->SetValues(args->Point.X(), args->Point.Y());
	}
}

void CreateBoxTool::_PivotAction_Finished(PointAction::EventArgs* args) {
	qDebug() << "Debug: CreateBoxTool::_PivotAction_Finished";

	PointAction* action = qobject_cast<PointAction*>(sender());
	if (action == nullptr) {
		return;
	}

	_Plane = WorkspaceController()->Workspace()->WorkingPlane();
	_PointPlane1 = args->PointOnPlane;

	StopAction(action);
	auto newAction = new PointAction();

	connect(newAction, &PointAction::Preview, this, &CreateBoxTool::_BaseRectAction_Preview);
	connect(newAction, &PointAction::Finished, this, &CreateBoxTool::_BaseRectAction_Finished);

	if (!StartAction(newAction))
		return;

	_CurrentPhase = Phase::BaseRect;
	SetHintMessage("Select opposite corner point, press `k:Ctrl` to round length and width to grid stepping.");

	//if (_MultiValueHudElement == nullptr)
	//{
	//	_MultiValueHudElement = new MultiValueHudElement()
	//	{
	//		Label1 = "Length:",
	//		Units1 = ValueUnits.Length,
	//		Label2 = "Width:",
	//		Units2 = ValueUnits.Length
	//	};
	//	_MultiValueHudElement.MultiValueEntered += _MultiValueEntered;
	//	Add(_MultiValueHudElement);
	//}
}

void CreateBoxTool::_BaseRectAction_Preview(PointAction::EventArgs* args) {
	qDebug() << "Debug: CreateBoxTool::_BaseRectAction_Preview";
}

void CreateBoxTool::_BaseRectAction_Finished(PointAction::EventArgs* args) {

}