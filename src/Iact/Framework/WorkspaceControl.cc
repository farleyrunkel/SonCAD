// Copyright [2024] SunCAD

#include "Iact/Framework/WorkspaceControl.h"

#include "Iact/Workspace/WorkspaceController.h"

WorkspaceControl::WorkspaceControl(QObject* parent) 
	: QObject(parent) ,
	m_workspaceController(nullptr) {
}

WorkspaceController* WorkspaceControl::workspaceController() const { 
	return m_workspaceController; 
}

void WorkspaceControl::setWorkspaceController(WorkspaceController* workspaceController) {
	m_workspaceController = workspaceController;
}

QList<WorkspaceControl*> WorkspaceControl::getChildren() const {
	return {};
}

void WorkspaceControl::add(HudElement* hudElement) {
	if (hudElement == nullptr || m_hudElements.contains(hudElement)) {
		return;
	}
	m_hudElements.append(hudElement);
}

