// Copyright [2024] SunCAD

#include "Iact/Visual/VisualObject.h"

#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>

#include "Iact/Workspace/WorkspaceController.h"



    VisualObject::VisualObject(const Handle(WorkspaceController)& workspaceController, const Handle(InteractiveEntity)& entity)
        : _WorkspaceController(workspaceController), _Entity(entity) {}

    Handle(AIS_InteractiveContext) VisualObject::AisContext() const {
        return  nullptr; // _WorkspaceController->Workspace()->aisContext();
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
