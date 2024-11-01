// Copyright [2024] SunCAD

#include "Iact/Framework/Tool.h"

#include "Iact/Workspace/WorkspaceController.h"

Tool::Tool(QObject* parent) : QObject() {}

void Tool::setWorkspaceController(WorkspaceController* controller) {
	m_workspaceController = controller;
}

bool Tool::start() {
	if (OnStart()) {
		m_isActive = true;
		m_workspaceController->invalidate();
		return true;
	}
	return false;
}

bool Tool::OnStart() { return false; }
