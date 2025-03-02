// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALOBJECT_H_
#define IACT_VISUAL_VISUALOBJECT_H_

#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <Standard_Transient.hxx>

// Forward declarations
class WorkspaceController;

class VisualObject : public Standard_Transient
{

protected:
    explicit VisualObject(const Handle(WorkspaceController)& theWC) {}

private:

};

#endif  // IACT_VISUAL_VISUALOBJECT_H_
