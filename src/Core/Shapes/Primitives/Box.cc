// Copyright [2024] SunCAD

#include "Core/Shapes/Primitives/Box.h"
#include <TCollection_AsciiString.hxx>

Box::Box() 
    : _DimensionX(1.0)
    , _DimensionY(1.0)
    , _DimensionZ(1.0)
{}

// DimensionX property

double Box::DimensionX() const
{
    return _DimensionX;
}

void Box::SetDimensionX(double value)
{
    if(!qFuzzyCompare(_DimensionX, value))
    {
        SaveUndo();
        _DimensionX = (value != 0.0) ? value : 0.001;
        Invalidate();
        OnDimensionXChanged(value);
    }
}

// DimensionY property

double Box::DimensionY() const
{
    return _DimensionY;
}

void Box::SetDimensionY(double value)
{
    if(!qFuzzyCompare(_DimensionY, value))
    {
        SaveUndo();
        _DimensionY = (value != 0.0) ? value : 0.001;
        Invalidate();
        OnDimensionYChanged(value);
    }
}

// DimensionZ property

double Box::DimensionZ() const
{
    return _DimensionZ;
}

void Box::SetDimensionZ(double value)
{
    if(!qFuzzyCompare(_DimensionZ, value))
    {
        SaveUndo();
        _DimensionZ = (value != 0.0) ? value : 0.001;
        Invalidate();
        OnDimensionZChanged(value);
    }
}

void Box::SaveUndo()
{
    // Implement undo logic
}

void Box::Invalidate()
{
    // Implement invalidation logic
}
