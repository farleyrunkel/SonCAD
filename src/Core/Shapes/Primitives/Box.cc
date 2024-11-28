// Copyright [2024] SunCAD

#include "Core/Shapes/Primitives/Box.h"

#include <QObject>

// Initialization

Sun_Box::Sun_Box()
    : _DimensionX(1.0), _DimensionY(1.0), _DimensionZ(1.0)
{
}

// DimensionX  Ù–‘

double Sun_Box::DimensionX() const
{
    return _DimensionX;
}

void Sun_Box::SetDimensionX(double value)
{
    if (!qFuzzyCompare(_DimensionX, value))
    {
        SaveUndo();
        _DimensionX = (value != 0.0) ? value : 0.001;
        Invalidate();
        emit DimensionXChanged(value);
    }
}


// DimensionY  Ù–‘

double Sun_Box::DimensionY() const
{
    return _DimensionY;
}

void Sun_Box::SetDimensionY(double value)
{
    if (!qFuzzyCompare(_DimensionY, value))
    {
        SaveUndo();
        _DimensionY = (value != 0.0) ? value : 0.001;
        Invalidate();
        emit DimensionYChanged(value);
    }
}


// DimensionZ  Ù–‘

double Sun_Box::DimensionZ() const
{
    return _DimensionZ;
}

void Sun_Box::SetDimensionZ(double value)
{
    if (!qFuzzyCompare(_DimensionZ, value))
    {
        SaveUndo();
        _DimensionZ = (value != 0.0) ? value : 0.001;
        Invalidate();
        emit DimensionZChanged(value);
    }
}


Sun_ShapeType Sun_Box::ShapeType() const
{
    return Sun_ShapeType::Solid;
}
