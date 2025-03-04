// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALOBJECT_H_
#define IACT_VISUAL_VISUALOBJECT_H_

#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
 

#include "Comm/BaseObject.h"

// Forward declarations
class WorkspaceController;


class VisualObject : public enable_property_changed_signal
{

protected:
    explicit VisualObject(const std::shared_ptr<WorkspaceController>& theWC) {}

private:

};

#endif  // IACT_VISUAL_VISUALOBJECT_H_
