#ifndef CORE_FRAMEWORK_OCCTUTILS_SUBSHAPETYPE_H_
#define CORE_FRAMEWORK_OCCTUTILS_SUBSHAPETYPE_H_

#include <functional>
#include <iostream>
#include <stdexcept>
#include <memory>

#include "Core/Topology/Entity.h"

enum SubshapeType
{
    Subshape_Vertex,
    Subshape_Edge,
    Subshape_Wire,
    Subshape_Face
};

enum SubshapeTypes
{
    None = 0,
    Vertex = 1 << 0,
    Edge = 1 << 1,
    Wire = 1 << 2,
    Face = 1 << 4,
    All = Vertex | Edge | Wire | Face
};

#endif  // CORE_FRAMEWORK_OCCTUTILS_SUBSHAPETYPE_H_
