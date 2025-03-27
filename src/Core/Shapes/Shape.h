// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_SHAPE_H_
#define CORE_SHAPES_SHAPE_H_

#include <QString>
#include <QList>

#include <TopoDS_Shape.hxx>
#include <Standard_Transient.hxx>
#include <NCollection_Vector.hxx>

#include "Core/Topology/Entity.h"
#include "Core/Topology/Body.h"
#include "Core/Shapes/IShapeOperand.h"

DEFINE_STANDARD_HANDLE(Shape, Standard_Transient)

// Base class for shape
class Shape : public Entity, public IShapeOperand, public IShapeDependent
{
	DEFINE_STANDARD_RTTI_INLINE(Shape, Entity)

public:
    enum MakeFlags
    {
        None = 0,
        DebugOutput = 1 << 1,
    };

    enum ShapeType
    {
        Unknown,
        Sketch,
        Solid,
        Mesh,
    };

public:
    Shape();

    struct NamedSubshape
    {};

    Handle(Body) GetBody();

private:
    bool _IsSkipped;
    bool _IsLoadedFromCache;
    bool _IsInvalidating;

    Handle(Body) _Body;

    TopoDS_Shape _BRep;
    TopoDS_Shape _TransformedBRep;

    NCollection_Vector<NamedSubshape> _NamedSubshapes;
};

#endif  // CORE_SHAPES_SHAPE_H_
