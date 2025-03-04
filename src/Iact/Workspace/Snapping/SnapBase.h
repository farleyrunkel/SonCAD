// Copyright (c) 2025 SunCAD
//
// This file is part of the SunCAD project.

#ifndef IACT_WORKSPACE_SNAPPING_SNAPBASE_H_
#define IACT_WORKSPACE_SNAPPING_SNAPBASE_H_

 
#include <Standard_Type.hxx>
#include "Comm/BaseObject.h"

class SnapBase : public enable_property_changed_signal
{
public:
	SnapBase() {}
};

#endif  // IACT_WORKSPACE_SNAPPING_SNAPBASE_H_
