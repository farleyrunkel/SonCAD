// Copyright [2024] SunCAD

#ifndef SRC_CORE_SHAPES_PRIMITIVES_BOX_H_
#define SRC_CORE_SHAPES_PRIMITIVES_BOX_H_

#include <BRepPrimAPI_MakeBox.hxx>

#include "Core/Shapes/Shape.h"

class Box : public Shape
{
public:
    // Name property, virtual
    virtual QString name() const {
        return "Box";
    }
    virtual void setName(const QString&) {}

    // Construction Properties
    double GetDimensionX() const
    {
        return _DimensionX;
    }

    void SetDimensionX(double value)
    {
        if (_DimensionX != value)
        {
            SaveUndo();
            _DimensionX = (value != 0.0) ? value : 0.001;
            Invalidate();
            RaisePropertyChanged();
        }
    }

    //--------------------------------------------------------------------------------------------------

    double GetDimensionY() const
    {
        return _DimensionY;
    }

    void SetDimensionY(double value)
    {
        if (_DimensionY != value)
        {
            SaveUndo();
            _DimensionY = (value != 0.0) ? value : 0.001;
            Invalidate();
            RaisePropertyChanged();
        }
    }

    //--------------------------------------------------------------------------------------------------

    double GetDimensionZ() const
    {
        return _DimensionZ;
    }

    void SetDimensionZ(double value)
    {
        if (_DimensionZ != value)
        {
            SaveUndo();
            _DimensionZ = (value != 0.0) ? value : 0.001;
            Invalidate();
            RaisePropertyChanged();
        }
    }

    //--------------------------------------------------------------------------------------------------

    // Initialization
    Box()
        : _DimensionX(1.0), _DimensionY(1.0), _DimensionZ(1.0)
    {
    }

    static Box* Create(double dimX, double dimY, double dimZ)
    {
        Box* box = new Box();
        box->SetDimensionX(dimX);
        box->SetDimensionY(dimY);
        box->SetDimensionZ(dimZ);
        return box;
    }

    ShapeType GetShapeType() const override
    {
        return ShapeType::Solid;
    }

//protected:
//    bool MakeInternal(Shape::MakeFlags flags) override
//    {
//        double dimX = (_DimensionX != 0.0) ? _DimensionX : 0.001;
//        double dimY = (_DimensionY != 0.0) ? _DimensionY : 0.001;
//        double dimZ = (_DimensionZ != 0.0) ? _DimensionZ : 0.001;
//
//        BRepPrimAPI_MakeBox makeBox(dimX, dimY, dimZ);
//        BRep = makeBox.Solid();
//
//        return Shape::MakeInternal(flags);
//    }

private:
    // Members
    double _DimensionX;
    double _DimensionY;
    double _DimensionZ;

    void SaveUndo() {
        // Implement undo-saving logic
    }

    void Invalidate() {
        // Implement invalidation logic
    }

    void RaisePropertyChanged() {
        // Implement property change notification
    }
};

#endif  // SRC_CORE_SHAPES_PRIMITIVES_BOX_H_
