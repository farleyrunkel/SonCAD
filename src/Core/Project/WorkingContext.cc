// Copyright [2024] SunCAD

#include "Core/Project/WorkingContext.h"

WorkingContext::WorkingContext()
    :
    _WorkingPlane(),
    _GridType(Workspace::GridTypes::Rectangular),
    _GridStep(1.0),
    _GridRotation(0),
    _GridDivisions(8)
{}

Handle(WorkingContext) WorkingContext::Clone() const
{
    Handle(WorkingContext) wc = new WorkingContext();
    wc->CopyFrom(*this);
    return wc;
}

void WorkingContext::CopyFrom(const WorkingContext& other)
{
    _WorkingPlane = other.GetWorkingPlane();
    _GridType = other.GridType();
    _GridStep = other.GridStep();
    _GridDivisions = other.GridDivisions();
    _GridRotation = other.GridRotation();
}

gp_Pln WorkingContext::GetWorkingPlane() const
{
    return _WorkingPlane;
}

void WorkingContext::SetWorkingPlane(const gp_Pln& plane)
{
    if(_WorkingPlane.Distance(plane) > gp::Resolution())
    {
        _WorkingPlane = plane;
        _OnWorkingPlaneChanged(plane);
    }
}

Workspace::GridTypes WorkingContext::GridType() const
{
    return _GridType;
}

void WorkingContext::SetGridType(Workspace::GridTypes type)
{
    if(_GridType != type)
    {
        _GridType = type;
        _OnGridTypeChanged(type);
    }
}

double WorkingContext::GridStep() const
{
    return _GridStep;
}

void WorkingContext::SetGridStep(double step)
{
    if(_GridStep != step)
    {
        _GridStep = step;
        _OnGridStepChanged(step);
    }
}

double WorkingContext::GridRotation() const
{
    return _GridRotation;
}

void WorkingContext::SetGridRotation(double rotation)
{
    if(_GridRotation != rotation)
    {
        _GridRotation = rotation;
        _OnGridRotationChanged(rotation);
    }
}

int WorkingContext::GridDivisions() const
{
    return _GridDivisions;
}

void WorkingContext::SetGridDivisions(int divisions)
{
    if(_GridDivisions != divisions)
    {
        _GridDivisions = divisions;
        _OnGridDivisionsChanged(divisions);
    }
}

// Helper methods to emit signals

void WorkingContext::_OnWorkingPlaneChanged(const gp_Pln& plane)
{
    OnWorkingPlaneChanged(plane);
}

void WorkingContext::_OnGridTypeChanged(Workspace::GridTypes type)
{
    OnGridTypeChanged(type);
}

void WorkingContext::_OnGridStepChanged(double step)
{
    OnGridStepChanged(step);
}

void WorkingContext::_OnGridRotationChanged(double rotation)
{
    OnGridRotationChanged(rotation);
}

void WorkingContext::_OnGridDivisionsChanged(int divisions)
{
    OnGridDivisionsChanged(divisions);
}
