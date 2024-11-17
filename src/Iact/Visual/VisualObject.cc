// Copyright [2024] SunCAD

#include "Iact/Visual/VisualObject.h"

#include <AIS_InteractiveContext.hxx>

#include "Iact/Workspace/WorkspaceController.h"

VisualObject::VisualObject(WorkspaceController* workspaceController, InteractiveEntity* entity, QObject* parent)
    : QObject(parent), m_workspaceController(workspaceController), m_entity(entity) {}

WorkspaceController* VisualObject::workspaceController() const { 
    return m_workspaceController; 
}

Handle(AIS_InteractiveContext) VisualObject::AisContext() const { 
    return m_workspaceController->workspace()->aisContext(); 
}

bool VisualObject::isSelected() const {
    return AisContext()->IsSelected(AisObject());
}

void VisualObject::setIsSelected(bool value) {
    if (AisContext()->IsSelected(AisObject()) != value) {
        AisContext()->AddOrRemoveSelected(AisObject(), false);
    }
}
