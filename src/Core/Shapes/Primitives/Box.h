// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_PRIMITIVES_BOX_H_
#define CORE_SHAPES_PRIMITIVES_BOX_H_

#include <boost/signals2.hpp>

#include <BRepPrimAPI_MakeBox.hxx>

#include "Core/Shapes/Shape.h"
#include "Core/Shapes/IShapeOperand.h"
#include "Comm/BaseObject.h"

DEFINE_STANDARD_HANDLE(Box, Shape)

class Box final : public Shape
{
public:
    // Initialization
    Box();

    // DimensionX property
    double DimensionX() const;

    void SetDimensionX(double value);

    // DimensionY property
    double DimensionY() const;

    void SetDimensionY(double value);

    // DimensionZ property
    double DimensionZ() const;

    void SetDimensionZ(double value);

    //virtual ShapeType GetShapeType() const  {
    //    return ShapeType::Solid;
    //}

public:
    // Signals
    boost::signals2::signal<void(double)> OnDimensionXChanged;
    boost::signals2::signal<void(double)> OnDimensionYChanged;
    boost::signals2::signal<void(double)> OnDimensionZChanged;

private:
    void SaveUndo();

    void Invalidate();

private:
    double _DimensionX = 0.0;
    double _DimensionY = 0.0;
    double _DimensionZ = 0.0;
};

#endif  // CORE_SHAPES_PRIMITIVES_BOX_H_
