// Copyright [2024] SunCAD

#include "Iact/Visual/VisualObject.h"

#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>

#include "Iact/Workspace/WorkspaceController.h"

VisualObject::VisualObject(WorkspaceController* workspaceController, InteractiveEntity* entity)
    : QObject(nullptr), _WorkspaceController(workspaceController), _Entity(entity) {}

WorkspaceController* VisualObject::workspaceController() const { 
    return _WorkspaceController; 
}

Handle(AIS_InteractiveContext) VisualObject::AisContext() const { 
    return _WorkspaceController->Workspace()->aisContext();
}

bool VisualObject::IsSelected() const {
    return AisContext()->IsSelected(AisObject());
}

void VisualObject::SetIsSelected(bool value) {
    if (AisContext()->IsSelected(AisObject()) != value) {
        AisContext()->AddOrRemoveSelected(AisObject(), false);
    }
}

void VisualObject::SetLocalTransformation(const gp_Trsf& transformation) {
    if (!AisObject()) return;
    AisObject()->SetLocalTransformation(transformation);
}
