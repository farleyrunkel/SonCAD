// Copyright [2024] SunCAD

#include "Iact/Visual/VisualObject.h"

#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>

#include "Iact/Workspace/WorkspaceController.h"

Sun_VisualObject::Sun_VisualObject(const Handle(Sun_WorkspaceController)& WorkspaceController, Sun_InteractiveEntity* entity)
    : _WorkspaceController(WorkspaceController), _Entity(entity) {}

Handle(Sun_WorkspaceController) Sun_VisualObject::WorkspaceController() const {
    return _WorkspaceController; 
}

Handle(AIS_InteractiveContext) Sun_VisualObject::AisContext() const { 
    return _WorkspaceController->Sun_Workspace()->aisContext();
}

bool Sun_VisualObject::IsSelected() const {
    return AisContext()->IsSelected(AisObject());
}

void Sun_VisualObject::SetIsSelected(bool value) {
    if (AisContext()->IsSelected(AisObject()) != value) {
        AisContext()->AddOrRemoveSelected(AisObject(), false);
    }
}

void Sun_VisualObject::SetLocalTransformation(const gp_Trsf& transformation) {
    if (!AisObject()) return;
    AisObject()->SetLocalTransformation(transformation);
}
