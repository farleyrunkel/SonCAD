// Copyright [2024] SunCAD

#include "Iact/Framework/Tool.h"

Tool::Tool(QObject* parent) : WorkspaceControl(),
	id(typeid(*this).name()) {
}

bool Tool::start() {
	if (OnStart()) {
		m_isActive = true;
		workspaceController()->invalidate();
		return true;
	}
	return false;
}

bool Tool::OnStart() { return false; }
