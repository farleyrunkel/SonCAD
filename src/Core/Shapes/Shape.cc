// Copyright [2024] SunCAD

#include "Core/Shapes/Shape.h"

#include "Core/Topology/Body.h"

Shape::Shape()
{}

Handle(Body) Shape::GetBody()
{
    return new Body;
}
