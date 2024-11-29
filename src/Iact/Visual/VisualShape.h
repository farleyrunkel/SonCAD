// Copyright [2024] SunCAD

#ifndef SRC_IACT_VISUAL_VISUALSHAPE_H_
#define SRC_IACT_VISUAL_VISUALSHAPE_H_

#include <AIS_InteractiveObject.hxx>
#include <Standard_Handle.hxx>

#include "Iact/Visual/VisualObject.h"

DEFINE_STANDARD_HANDLE(Sun_VisualShape, Standard_Transient);

class Sun_VisualShape : public Sun_VisualObject 
{
public:
    explicit Sun_VisualShape(const Handle(Sun_WorkspaceController)& WorkspaceController, Sun_InteractiveEntity* entity)
    : Sun_VisualObject(WorkspaceController, entity) {}

    virtual void Remove() override {}

    virtual void Update() override {}

    virtual Handle(AIS_InteractiveObject) AisObject() const override 
    {
        return Handle(AIS_InteractiveObject) {};
    }


};

#endif  // SRC_IACT_VISUAL_VISUALSHAPE_H_
