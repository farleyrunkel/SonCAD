// Copyright [2024] SunCAD

#include "Core/Project/WorkingContext.h"

// Getter ºÍ Setter ·½·¨

gp_Pln WorkingContext::workingPlane() const { return _WorkingPlane; }

void WorkingContext::setWorkingPlane(const gp_Pln& plane) { _WorkingPlane = plane; }

Sun::Workspace::GridTypes WorkingContext::gridType() const { return _GridType; }

void WorkingContext::setGridType(Sun::Workspace::GridTypes type) { _GridType = type; }

double WorkingContext::gridStep() const { return _GridStep; }

void WorkingContext::setGridStep(double step) { _GridStep = step; }

double WorkingContext::gridRotation() const { return _GridRotation; }

void WorkingContext::setGridRotation(double rotation) { _GridRotation = rotation; }

int WorkingContext::gridDivisions() const { return _GridDivisions; }

void WorkingContext::setGridDivisions(int divisions) { _GridDivisions = divisions; }
