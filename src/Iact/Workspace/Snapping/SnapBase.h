// Copyright (c) 2025 SunCAD
//
// This file is part of the SunCAD project.

#ifndef IACT_WORKSPACE_SNAPPING_SNAPBASE_H_
#define IACT_WORKSPACE_SNAPPING_SNAPBASE_H_

#include <Standard_Transient.hxx>
#include <Standard_Type.hxx>

DEFINE_STANDARD_HANDLE(SnapBase, Standard_Transient)

class SnapBase : public Standard_Transient
{
public:
	SnapBase() {}
};

#endif  // IACT_WORKSPACE_SNAPPING_SNAPBASE_H_
