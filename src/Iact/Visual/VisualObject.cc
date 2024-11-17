// Copyright [2024] SunCAD

#include "Iact/Visual/VisualObject.h"

#include <AIS_InteractiveContext.hxx>

#include "Iact/Workspace/WorkspaceController.h"

VisualObject::VisualObject(WorkspaceController* workspaceController, InteractiveEntity* entity, QObject* parent)
    : QObject(parent), m_workspaceController(workspaceController), m_entity(entity) {}

WorkspaceController* VisualObject::workspaceController() const { 
    return m_workspaceController; 
}

Handle(AIS_InteractiveContext) VisualObject::aisContext() const { 
    return m_workspaceController->workspace()->aisContext(); 
}

bool VisualObject::isSelected() const {
    return aisContext()->IsSelected(aisObject());
}

void VisualObject::setIsSelected(bool value) {
    if (aisContext()->IsSelected(aisObject()) != value) {
        aisContext()->AddOrRemoveSelected(aisObject(), false);
    }
}
