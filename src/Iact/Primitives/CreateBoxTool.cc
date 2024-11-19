// Copyright [2024] SunCAD

#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/HudElements/Coord2DHudElement.h"

CreateBoxTool::CreateBoxTool() 
	: Tool(),
	_Coord2DHudElement(nullptr) {
	
}

bool CreateBoxTool::OnStart() {
	qDebug() << "Debug: CreateBoxTool::OnStart";
	m_currentPhase = Phase::PivotPoint;
	auto pointAction = new PointAction();
	if (!startAction(pointAction)) {
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
}
