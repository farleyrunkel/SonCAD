
#include "Core/Project/Viewport.h"

#include "Core/Project/Workspace.h"

Viewport::Viewport(const Handle(Workspace)& workspace) 
    : myWorkspace(workspace)
{}

bool Viewport::ScreenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt)
{
    return false;
}
