//// Copyright [2024] SunCAD

#ifndef SRC_CORE_SHAPES_PRIMITIVES_BOX_H_
#define SRC_CORE_SHAPES_PRIMITIVES_BOX_H_

#include <QObject>

#include <BRepPrimAPI_MakeBox.hxx>

#include "Core/Shapes/Shape.h"
#include "Core/Shapes/IShapeOperand.h"

DEFINE_STANDARD_HANDLE(Sun_Box, Standard_Transient)

class Sun_Box final : public Sun_Shape
{
    Q_OBJECT
    Q_PROPERTY(double DimensionX READ DimensionX WRITE SetDimensionX NOTIFY DimensionXChanged)
    Q_PROPERTY(double DimensionY READ DimensionY WRITE SetDimensionY NOTIFY DimensionYChanged)
    Q_PROPERTY(double DimensionZ READ DimensionZ WRITE SetDimensionZ NOTIFY DimensionZChanged)

public:
    // 类名属性
    virtual QString Name() const override {
        return "Sun_Box";
    }

    virtual void SetName(const QString&) override {}

    // DimensionX 属性
    double DimensionX() const;

    void SetDimensionX(double value);

    // DimensionY 属性
    double DimensionY() const;

    void SetDimensionY(double value);

    // DimensionZ 属性
    double DimensionZ() const;

    void SetDimensionZ(double value);

    // Initialization
    Sun_Box();

    //static Sun_Box* Create(double dimX, double dimY, double dimZ)
    //{
    //    Sun_Box* box = new Sun_Box();
    //    box->SetDimensionX(dimX);
    //    box->SetDimensionY(dimY);
    //    box->SetDimensionZ(dimZ);
    //    return box;
    //}

    virtual Sun_ShapeType ShapeType() const override;

signals:
    void DimensionXChanged(double);
    void DimensionYChanged(double);
    void DimensionZChanged(double);

private:
    void SaveUndo() {
        // 实现保存撤销逻辑
    }

    void Invalidate() {
        // 实现无效化逻辑
    }

private:
    double _DimensionX = 0.0;
    double _DimensionY = 0.0;
    double _DimensionZ = 0.0;
};

#endif  // SRC_CORE_SHAPES_PRIMITIVES_BOX_H_
