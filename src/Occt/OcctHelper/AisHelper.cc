// Copyright [2024] SunCAD

// Own include
#include "Occt/OcctHelper/AisHelper.h"

// Occt includes
#include <PrsMgr_PresentableObject.hxx>
#include <SelectMgr_EntityOwner.hxx>
#include <StdSelect_BRepOwner.hxx>
#include <TopoDS_Shape.hxx>

void AisHelper::DisableGlobalClipPlanes(const Handle(PrsMgr_PresentableObject)& object)
{
	auto seq = new Graphic3d_SequenceOfHClipPlane();
	seq->SetOverrideGlobal(true);
	object->SetClipPlanes(seq);
}

TopoDS_Shape AisHelper::GetShapeFromEntityOwner(const Handle(SelectMgr_EntityOwner) owner)
{
	if (owner.IsNull())
		return {};

	auto brepOwner = Handle(StdSelect_BRepOwner)::DownCast(owner);
	if (brepOwner.IsNull() || !brepOwner->HasShape())
		return {};

	return TopoDS_Shape(brepOwner->Shape());
}

void AisHelper::SetRubberbandPoints(const Handle(Aspect_Window)& wntWindow, 
									const Handle(AIS_RubberBand)& aisRubberband, std::vector<Graphic3d_Vec2i>& pointList)
{
	Standard_Integer width, height;
	wntWindow->Size(width, height);
	auto rubberband = aisRubberband;
	rubberband->ClearPoints();
	for (auto point : pointList)
	{
		Graphic3d_Vec2i vec2i(point.x(), height - point.y());
		rubberband->AddPoint(vec2i);
	}
}
