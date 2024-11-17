// Copyright [2024] SunCAD

#include "Iact/Framework/WorkspaceControl.h"

#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Visual/VisualObject.h"

WorkspaceControl::WorkspaceControl(QObject* parent) 
	: QObject(parent) ,
	_WorkspaceController(nullptr) {
}

WorkspaceController* WorkspaceControl::workspaceController() const { 
	return _WorkspaceController; 
}

void WorkspaceControl::setWorkspaceController(WorkspaceController* workspaceController) {
	_WorkspaceController = workspaceController;
}

QList<WorkspaceControl*> WorkspaceControl::GetChildren() const {
	return {};
}

void WorkspaceControl::Add(HudElement* hudElement) {
	if (hudElement == nullptr || _HudElements.contains(hudElement)) {
		return;
	}
	_HudElements.append(hudElement);
}

void WorkspaceControl::SetHintMessage(const QString& message) {
	auto hudManager = workspaceController()->hudManager();
	if (hudManager)
		hudManager->SetHintMessage(message);
}

void WorkspaceControl::Add(VisualObject* visual) {
	if (_VisualObjects.contains(visual))
		return;
	_VisualObjects.append(visual);
	workspaceController()->Invalidate();
}
