// Copyright [2024] SunCAD

#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/HudElements/Coord2DHudElement.h"

CreateBoxTool::CreateBoxTool() 
	: Tool(),
	m_coord2DHudElement(nullptr) {
	
}

bool CreateBoxTool::onStart() {
	qDebug() << "Debug: CreateBoxTool::onStart";
	m_currentPhase = Phase::PivotPoint;
	auto pointAction = new PointAction();
	if (!startAction(pointAction)) {
		return false;
	}
	connect(pointAction, &PointAction::preview, this, &CreateBoxTool::pivotAction_preview);
	connect(pointAction, &PointAction::finished, this, &CreateBoxTool::pivotAction_finished);

	setHintMessage("Select corner point.");

	m_coord2DHudElement = new Coord2DHudElement;
	add(m_coord2DHudElement);
	return true;
}

void CreateBoxTool::pivotAction_preview() {
	qDebug() << "Debug: CreateBoxTool::pivotAction_preview";
	// m_coord2DHudElement

}


void CreateBoxTool::pivotAction_finished() {
	qDebug() << "Debug: CreateBoxTool::pivotAction_finished";
}
