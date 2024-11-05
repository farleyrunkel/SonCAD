// Copyright [2024] SunCAD

#include "Iact/Framework/WorkspaceControl.h"

#include "Iact/Workspace/WorkspaceController.h"

WorkspaceControl::WorkspaceControl(QObject* parent) {}

WorkspaceController* WorkspaceControl::workspaceController() const { return m_workspaceController; }

