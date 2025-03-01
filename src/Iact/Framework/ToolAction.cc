// Copyright [2024] SunCAD

#include "Iact/Framework/ToolAction.h"

#include "Iact/Framework/WorkspaceControl.h"

ToolAction::ToolAction()
{}

void ToolAction::Stop()
{
    OnStop();
    WorkspaceControl::Cleanup();
}
