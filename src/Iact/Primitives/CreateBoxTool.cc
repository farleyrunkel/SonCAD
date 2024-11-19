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
	auto pointAction = std::make_shared<PointAction>();
	if (!startAction(pointAction.get())) {
		return false;
	}

	connect(pointAction.get(), &PointAction::Preview, this, &CreateBoxTool::_PivotAction_Preview);
	connect(pointAction.get(), &PointAction::Finished, this, &CreateBoxTool::_PivotAction_Finished);

	SetHintMessage("Select corner point.");

	_Coord2DHudElement = new Coord2DHudElement;
	Add(_Coord2DHudElement);
	return true;
}

void CreateBoxTool::_PivotAction_Preview(const std::shared_ptr<PointAction::EventArgs>& args) {
	qDebug() << "Debug: CreateBoxTool::_PivotAction_Preview";
	if (_Coord2DHudElement) {
		_Coord2DHudElement->SetValues(args->Point.X(), args->Point.Y());
	}
}

void CreateBoxTool::_PivotAction_Finished(const std::shared_ptr<PointAction::EventArgs>& args) {
	qDebug() << "Debug: CreateBoxTool::_PivotAction_Finished";
}
