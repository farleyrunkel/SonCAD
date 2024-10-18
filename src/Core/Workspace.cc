// Copyright [2024] SonCAD

#include "Core/Workspace.h"

Workspace::Workspace() {
}

void Workspace::initViewer() {
}

Handle(V3d_Viewer) Workspace::V3dViewer() const {
    return v3dViewer;
}

