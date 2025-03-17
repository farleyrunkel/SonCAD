// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_MOUSEEVENTDATA_H_
#define IACT_WORKSPACE_MOUSEEVENTDATA_H_

#include <optional>
#include <QGraphicsView>
#include <QList>
#include <QMouseEvent>
#include <QPointF>

#include <AIS_InteractiveObject.hxx>
#include <gp_Pnt.hxx>
#include <TopoDS_Shape.hxx>

#include "Core/Topology/InteractiveEntity.h"
#include "Core/Viewport.h"

class MouseEventData;

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class MouseEventData 
{
public:
    struct Element 
    {
        Handle(AIS_InteractiveObject) aisObject;
        Handle(InteractiveEntity) entity;
        TopoDS_Shape brepShape;

        Element(const Handle(AIS_InteractiveObject)& aisObj, const Handle(InteractiveEntity)& ent, const TopoDS_Shape& brep)
            : aisObject(aisObj), entity(ent), brepShape(brep) {}

        Element(const Handle(AIS_InteractiveObject)& aisObj, const TopoDS_Shape& brep = TopoDS_Shape())
            : aisObject(aisObj), brepShape(brep) {}

        Element(const Handle(InteractiveEntity)& ent)
            : entity(ent) {}
    };

    // 返回选项类
    class ReturnOptions 
    {
    public:
        QList<Element> additionalHighlights;
        bool forceReDetection = false;
        bool removeHighlighting = false;

        // 清空返回选项数据
        void Clear() 
        {
            additionalHighlights.clear();
            forceReDetection = false;
            removeHighlighting = false;
        }
    };

public:
    // 构造函数
    MouseEventData() {}
    MouseEventData(const Handle(Viewport)& vp, const QPointF& sp, const gp_Pnt& pp, Qt::KeyboardModifiers mk)
        : _Viewport(vp), _ScreenPoint(sp), PointOnPlane(pp), ModifierKeys(mk) {}

    // 检测到的主要实体
    Handle(InteractiveEntity) DetectedEntity() const;

    TopoDS_Shape DetectedBrepShape() const {
        return !_DetectedElements.isEmpty() ? _DetectedElements[0].brepShape : TopoDS_Shape();
    }

    Handle(AIS_InteractiveObject) DetectedAisObject() const;

    void Clear();

    void Set(const Handle(Viewport)& vp, const QPointF& sp, const gp_Pnt& pp, Qt::KeyboardModifiers mk);

    void SetDetectedElements(const QList<Handle(AIS_InteractiveObject)>& aisObjects,
                             const QList<Handle(InteractiveEntity)>& entities,
                             const QList<TopoDS_Shape>& brepShapes);

    void SetDetectedElement(const Handle(AIS_InteractiveObject)& aisObject, 
                            const Handle(InteractiveEntity)& entity, 
                            const TopoDS_Shape& brepShape);

    //// 获取拾取轴
    //Ax1 pickAxis() const {
    //    return viewport->ViewAxis(screenPoint.x(), screenPoint.y());
    //}
    Handle(Viewport) _Viewport = nullptr;
    QPointF _ScreenPoint;
    gp_Pnt PointOnPlane;
    Qt::KeyboardModifiers ModifierKeys;
    QList<Element> _DetectedElements;
    ReturnOptions _ReturnOptions;
};

#endif  // IACT_WORKSPACE_MOUSEEVENTDATA_H_
