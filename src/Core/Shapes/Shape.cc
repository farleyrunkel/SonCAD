// Copyright [2024] SunCAD

#include "Core/Shapes/Shape.h"

#include "Core/Topology/Body.h"

Shape::Shape()
	: Entity()
	, _IsSkipped(false)
	, _IsLoadedFromCache(false)
	, _IsInvalidating(false)
	, _Body(new Body)
	, _BRep()
	, _TransformedBRep()
{
    _Name = get_type_name();
}

Handle(Body) Shape::GetBody()
{
    return _Body;
}
