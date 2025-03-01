#ifndef CORE_SHAPES_ISHAPEOPERAND_H_
#define CORE_SHAPES_ISHAPEOPERAND_H_

#include <optional>

#include "TopoDS_Shape.hxx" 
#include "gp_Ax3.hxx"       
#include "gp_Pln.hxx"       

enum class ShapeType
{
    Solid,
    Shell,
    Wire,
    Face,
    Edge,
    Vertex
};

//--------------------------------------------------------------------------------------------------

class IShapeDependent
{
public:
    virtual ~IShapeDependent() = default;
};

//--------------------------------------------------------------------------------------------------

class IShapeOperand
{
public:
    virtual ~IShapeOperand() = default;

    //virtual ShapeType ShapeType() const
    //{};
};


#endif // CORE_SHAPES_ISHAPEOPERAND_H_
