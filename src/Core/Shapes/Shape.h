// Copyright [2024] SunCAD

#ifndef CORE_SHAPES_SHAPE_H_
#define CORE_SHAPES_SHAPE_H_

#include <gp_Trsf.hxx>
#include <NCollection_Vector.hxx>
#include <TCollection_AsciiString.hxx>
#include <TopoDS_Shape.hxx>

#include "Core/Framework/OcctUtils/SubshapeType.h"
#include "Core/Topology/Entity.h"

// Base class for shape
class Body;

enum ShapeType 
{
    Unknown,
    Sketch,
    Solid,
    Mesh,
};

class Shape : public Entity
{

public:
    enum MakeFlags
    {
        None = 0,
        DebugOutput = 1 << 1,
    };

public:
    Shape() {}

    struct NamedSubshape 
    {
         SubshapeType Type;
         TCollection_AsciiString Name;
         int Index;
         TopoDS_Shape Shape;
    };

public:

private:
    bool m_IsSkipped;
    bool m_IsLoadedFromCache;
    bool m_IsInvalidating;

    std::shared_ptr<Body> m_Body;
private:
    TCollection_AsciiString m_Name;

    TopoDS_Shape m_BRep;
    TopoDS_Shape m_TransformedBRep;
    NCollection_Vector<NamedSubshape> m_NamedSubshapes;
};

#endif  // CORE_SHAPES_SHAPE_H_
