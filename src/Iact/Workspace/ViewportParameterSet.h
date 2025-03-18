
// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_ViewportParameterSet_H_
#define IACT_WORKSPACE_ViewportParameterSet_H_

#include "Comm/ParameterSets.h"

class ViewportParameterSet final : public OverridableParameterSet
{
public:
    ViewportParameterSet()
    {
        SetDefaultValue("SketchSelectionSensitivity", 1);
        SetDefaultValue("SelectionPixelTolerance", 5);
        SetDefaultValue("ShowViewCube", true);
        SetDefaultValue("ViewCubeSize", 50);
        SetDefaultValue("ViewCubeAnimationDuration", 0.3);
        SetDefaultValue("ShowTrihedron", true);
        SetDefaultValue("EnableAntialiasing", true);
    }

    int SketchSelectionSensitivity() const { return GetValue<int>("SketchSelectionSensitivity"); }
	int SelectionPixelTolerance() const { return GetValue<int>("SelectionPixelTolerance"); }
	bool ShowViewCube() const { return GetValue<bool>("ShowViewCube"); }
	int ViewCubeSize() const { return GetValue<int>("ViewCubeSize"); }
	double ViewCubeAnimationDuration() const { return GetValue<double>("ViewCubeAnimationDuration"); }
	bool ShowTrihedron() const { return GetValue<bool>("ShowTrihedron"); }
	bool EnableAntialiasing() const { return GetValue<bool>("EnableAntialiasing"); }
};

#endif // IACT_WORKSPACE_ViewportParameterSet_H_
