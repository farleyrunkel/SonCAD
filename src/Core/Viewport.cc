// Copyright [2024] SunCAD

#include "Core/Viewport.h"

Viewport::Viewport(const Handle(Workspace)& workspace)
    : _Workspace(workspace), _RenderMode(SolidShaded), _Twist(0.0), _Scale(100.0)
{}
