// Copyright [2024] SunCAD

#include "Iact/HudElements/HudElement.h"

#include "Iact/Workspace/WorkspaceController.h"

HudElement::HudElement(QWidget* parent) : QWidget(parent) {
	setMinimumHeight(25);
}

WorkspaceController* HudElement::workspaceController() const { 
	return m_workspaceController; 
}
