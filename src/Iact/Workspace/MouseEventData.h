// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_MOUSEEVENTDATA_H_
#define IACT_WORKSPACE_MOUSEEVENTDATA_H_

#include <optional>
#include <QGraphicsView>
#include <QList>
#include <QMouseEvent>
#include <QPointF>

#include <AIS_InteractiveObject.hxx>
#include <Aspect_VKeyFlags.hxx>
#include <gp_Ax1.hxx>
#include <gp_Pnt.hxx>
#include <NCollection_Vector.hxx>
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

    class ReturnOptions 
    {
    public:
        NCollection_Vector<Element> additionalHighlights;
        bool forceReDetection = false;
        bool removeHighlighting = false;

        void Clear() 
        {
            additionalHighlights.Clear();
            forceReDetection = false;
            removeHighlighting = false;
        }
    };

public:
    MouseEventData() {}

    MouseEventData(const Handle(Viewport)& vp, const Graphic3d_Vec2d& sp, const gp_Pnt& pp, Aspect_VKeyFlags mk)
        : _Viewport(vp), _ScreenPoint(sp), _PointOnPlane(pp), _ModifierKeys(mk)
    {}

    Handle(InteractiveEntity) DetectedEntity() const;

    TopoDS_Shape DetectedBrepShape() const;

    Handle(AIS_InteractiveObject) DetectedAisObject() const;

    void Clear();

    void Set(const Handle(Viewport)& vp, 
             const Graphic3d_Vec2d& sp, 
             const gp_Pnt& pp, 
             Aspect_VKeyFlags mk);

    void SetDetectedElements(const NCollection_Vector<Handle(AIS_InteractiveObject)>& aisObjects,
                             const NCollection_Vector<Handle(InteractiveEntity)>& entities,
                             const NCollection_Vector<TopoDS_Shape>& brepShapes);

    void SetDetectedElement(const Handle(AIS_InteractiveObject)& aisObject, 
                            const Handle(InteractiveEntity)& entity, 
                            const TopoDS_Shape& brepShape);

    gp_Ax1 PickAxis() const;

    // getter
	Handle(Viewport) GetViewport() const { return _Viewport; }
	gp_Pnt PointOnPlane() const { return _PointOnPlane; }
	NCollection_Vector<Element> DetectedElements() const { return _DetectedElements; }
	ReturnOptions GetReturnOptions() const { return _ReturnOptions; }

	// setter
	void SetViewport(const Handle(Viewport)& vp) { _Viewport = vp; }
	void SetPointOnPlane(const gp_Pnt& pp) { _PointOnPlane = pp; }
	void SetDetectedElements(const NCollection_Vector<Element>& elements) { _DetectedElements = elements; }
	void SetReturnOptions(const ReturnOptions& options) { _ReturnOptions = options; }

private:
    Handle(Viewport) _Viewport;
    gp_Pnt _PointOnPlane;
    NCollection_Vector<Element> _DetectedElements;
    ReturnOptions _ReturnOptions;
    Graphic3d_Vec2d _ScreenPoint;
    Aspect_VKeyFlags _ModifierKeys;
};

#endif  // IACT_WORKSPACE_MOUSEEVENTDATA_H_
