// Copyright [2024] SunCAD

#include "Iact/Primitives/CreateBoxTool.h"

CreateBoxTool::CreateBoxTool() : Tool() {}

bool CreateBoxTool::onStart() {
	qDebug() << "Debug: CreateBoxTool::onStart";
	m_currentPhase = Phase::PivotPoint;
	auto pointAction = new PointAction();
	if (!startAction(pointAction)) {
		return false;
	}
	connect(pointAction, &PointAction::preview, this, &CreateBoxTool::_PivotAction_Preview);
	connect(pointAction, &PointAction::finished, this, &CreateBoxTool::_PivotAction_Finished);

	return true;
}

