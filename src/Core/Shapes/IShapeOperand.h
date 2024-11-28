#ifndef SRC_CORE_SHAPES_ISHAPEOPERAND_H_
#define SRC_CORE_SHAPES_ISHAPEOPERAND_H_

#include <optional>

#include "TopoDS_Shape.hxx" // OpenCASCADE �����˽ṹ����
#include "gp_Ax3.hxx"       // OpenCASCADE �� 3D ����ϵ
#include "gp_Pln.hxx"       // OpenCASCADE ��ƽ������

enum class Sun_ShapeType
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

    virtual Sun_ShapeType ShapeType() const = 0;
};

//--------------------------------------------------------------------------------------------------

#endif // SRC_CORE_SHAPES_ISHAPEOPERAND_H_
