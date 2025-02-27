// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_SHAPE_H_
#define CORE_SHAPES_SHAPE_H_

#include <QString>
#include <QList>

#include <TopoDS_Shape.hxx>
#include <Standard_Transient.hxx>

#include "Core/Topology/Entity.h"
#include "Core/Topology/Body.h"
#include "Core/Shapes/IShapeOperand.h"

DEFINE_STANDARD_HANDLE(Shape, Standard_Transient)

// Base class for shape
class Shape : public Entity, public IShapeOperand, public IShapeDependent
{

 public:
    Shape() {}

    struct NamedSubshape
    {
    };

    Handle(Body) GetBody();

    //virtual Sun_ShapeType ShapeType() const = 0;

 private:
    bool _IsSkipped;
    bool _IsLoadedFromCache;
    bool _IsInvalidating;
    Handle(Body) _Body = new Body;
    QString _Name;
    Handle(TopoDS_Shape) _BRep;
    Handle(TopoDS_Shape) _TransformedBRep;
    QList<NamedSubshape> _NamedSubshapes;
};

#endif  // CORE_SHAPES_SHAPE_H_
