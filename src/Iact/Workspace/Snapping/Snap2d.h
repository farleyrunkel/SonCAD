// Copyright (c) 2025 SunCAD
//
// This file is part of the SunCAD project.

#ifndef IACT_WORKSPACE_SNAPPING_SNAP2D_H_
#define IACT_WORKSPACE_SNAPPING_SNAP2D_H_

#include "Iact/Workspace/Snapping/SnapBase.h"

#include <Standard_Transient.hxx>
#include <Standard_Type.hxx>

DEFINE_STANDARD_HANDLE(Snap2d, SnapBase)

class Snap2d : public SnapBase
{
public:
	Snap2d() {}
};


#endif  // IACT_WORKSPACE_SNAPPING_SNAP2D_H_
