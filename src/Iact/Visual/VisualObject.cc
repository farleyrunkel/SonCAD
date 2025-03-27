// Copyright [2024] SunCAD

#include "Iact/Visual/VisualObject.h"

#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>

#include "Iact/Workspace/WorkspaceController.h"


VisualObject::VisualObject(const Handle(WorkspaceController)& workspaceController,
                           const Handle(InteractiveEntity)& entity)
    : _WorkspaceController(workspaceController)
    , _Entity(entity)
{}

Handle(WorkspaceController) VisualObject::GetWorkspaceController() const
{
    return _WorkspaceController;
}

Handle(AIS_InteractiveContext) VisualObject::AisContext() const
{
    return  _WorkspaceController->GetWorkspace()->AisContext();
}

Handle(InteractiveEntity) VisualObject::Entity() const
{
    return _Entity;
}

bool VisualObject::IsSelected() const
{
    return AisContext()->IsSelected(AisObject());
}

void VisualObject::SetIsSelected(bool value)
{
    if(AisContext()->IsSelected(AisObject()) != value)
    {
        AisContext()->AddOrRemoveSelected(AisObject(), false);
    }
}

std::any VisualObject::Tag() const
{
    return _Tag;
}

inline void VisualObject::SetTag(const std::any& tag)
{
    _Tag = tag;
}

void VisualObject::SetLocalTransformation(const gp_Trsf& transformation)
{
    if(AisObject().IsNull()) return;
    AisObject()->SetLocalTransformation(transformation);
}

bool VisualObject::IsSelectable() const
{
    return false;
}

void VisualObject::SetIsSelectable(bool value)
{}
