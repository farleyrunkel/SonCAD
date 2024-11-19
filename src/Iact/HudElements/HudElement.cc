// Copyright [2024] SunCAD

#include "Iact/HudElements/HudElement.h"

#include "Iact/Workspace/WorkspaceController.h"

WorkspaceController* IHudElement::workspaceController() const { 
	return m_workspaceController; 
}
