// Copyright [2024] SunCAD

#include "Iact/Workspace/MouseEventData.h"

#include <AIS_InteractiveObject.hxx>
#include <Aspect_VKeyFlags.hxx>
#include <gp_Pnt.hxx>
#include <NCollection_Vector.hxx>
#include <TopoDS_Shape.hxx>

#include "Core/Viewport.h"

Handle(InteractiveEntity) MouseEventData::DetectedEntity() const
{
    return !_DetectedElements.IsEmpty() ? _DetectedElements[0].entity : nullptr;
}

TopoDS_Shape MouseEventData::DetectedBrepShape() const
{
    return !_DetectedElements.IsEmpty() ? _DetectedElements[0].brepShape : TopoDS_Shape();
}

Handle(AIS_InteractiveObject) MouseEventData::DetectedAisObject() const
{
    return !_DetectedElements.IsEmpty() ? _DetectedElements[0].aisObject : nullptr;
}

void MouseEventData::Clear()
{
    _Viewport.Nullify();
    _ScreenPoint = Graphic3d_Vec2d();
    _PointOnPlane = gp_Pnt();
    _DetectedElements.Clear();
    _ReturnOptions.Clear();
}

void MouseEventData::Set(const Handle(Viewport)& vp, const Graphic3d_Vec2d& sp, const gp_Pnt& pp, Aspect_VKeyFlags mk)
{
    Clear();
	_Viewport = vp;
	_ScreenPoint = sp;
	_PointOnPlane = pp;
	_ModifierKeys = mk;
}

void MouseEventData::SetDetectedElements(const NCollection_Vector<Handle(AIS_InteractiveObject)>& aisObjects, 
                                         const NCollection_Vector<Handle(InteractiveEntity)>& entities, 
                                         const NCollection_Vector<TopoDS_Shape>& brepShapes)
{
    _DetectedElements.Clear();
    auto e1 = aisObjects.begin();
    auto e2 = entities.begin();
    auto e3 = brepShapes.begin();

    while(e1 != aisObjects.end() || e2 != entities.end() || e3 != brepShapes.end())
    {
        Handle(AIS_InteractiveObject) c1 = (e1 != aisObjects.end()) ? *e1++ : nullptr;
        Handle(InteractiveEntity) c2 = (e2 != entities.end()) ? *e2++ : nullptr;
        TopoDS_Shape c3 = (e3 != brepShapes.end()) ? *e3++ : TopoDS_Shape();
        _DetectedElements.Append(Element(c1, c2, c3));
    }
}

// 设置单个检测元素

void MouseEventData::SetDetectedElement(const Handle(AIS_InteractiveObject)& aisObject, 
                                        const Handle(InteractiveEntity)& entity,
                                        const TopoDS_Shape& brepShape)
{
    _DetectedElements.Clear();
    _DetectedElements.Append(Element(aisObject, entity, brepShape));
}

gp_Ax1 MouseEventData::PickAxis() const
{
    return _Viewport->ViewAxis(_ScreenPoint.x(), _ScreenPoint.y());
}
