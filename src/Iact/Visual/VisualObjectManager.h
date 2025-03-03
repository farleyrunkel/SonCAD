// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VisualObjectManager_H_
#define IACT_VISUAL_VisualObjectManager_H_

#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <Standard_Transient.hxx>

// Forward declarations
class WorkspaceController;

DEFINE_STANDARD_HANDLE(VisualObjectManager, Standard_Transient)

class VisualObjectManager : public Standard_Transient
{

protected:
    explicit VisualObjectManager() {}

private:

};

#endif  // IACT_VISUAL_VisualObjectManager_H_
