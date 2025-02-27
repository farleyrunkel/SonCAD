// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALSHAPE_H_
#define IACT_VISUAL_VISUALSHAPE_H_

#include <AIS_InteractiveObject.hxx>
#include <Standard_Handle.hxx>

#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/WorkspaceController.h"



DEFINE_STANDARD_HANDLE(VisualShape, Standard_Transient);

class VisualShape : public VisualObject 
{
public:
    explicit VisualShape(const Handle(WorkspaceController)& WorkspaceController, const Handle(InteractiveEntity)& entity)
    : VisualObject(WorkspaceController, entity) {}

    virtual void Remove() override {}

    virtual void Update() override {}

    virtual Handle(AIS_InteractiveObject) AisObject() const override 
    {
        return Handle(AIS_InteractiveObject) {};
    }
};

#endif  // IACT_VISUAL_VISUALSHAPE_H_
