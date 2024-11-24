// Copyright [2024] SunCAD

#ifndef SRC_CORE_SHAPES_SHAPE_H_
#define SRC_CORE_SHAPES_SHAPE_H_

#include <QString>
#include <QList>

#include <TopoDS_Shape.hxx>

#include "Core/Topology/Entity.h"
#include "Core/Topology/Body.h"
#include "Core/Shapes/IShapeOperand.h"

// Base class for shape
class Shape : public Entity, public IShapeOperand, public IShapeDependent
{
    Q_OBJECT

 public:
    Shape() {}

    struct NamedSubshape
    {
    };

    Body* body() {
        return new Body;
    }

 private:
    bool _IsSkipped;
    bool _IsLoadedFromCache;
    bool _IsInvalidating;
    Body _Body;
    QString _Name;
    Handle(TopoDS_Shape) _BRep;
    Handle(TopoDS_Shape) _TransformedBRep;
    QList<NamedSubshape> _NamedSubshapes;
};

#endif  // SRC_CORE_SHAPES_SHAPE_H_
