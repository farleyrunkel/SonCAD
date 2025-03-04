// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VisualObjectManager_H_
#define IACT_VISUAL_VisualObjectManager_H_

#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>

#include "Comm/BaseObject.h"

// Forward declarations
class WorkspaceController;

class VisualObjectManager : public enable_property_changed_signal
{

protected:
    explicit VisualObjectManager() {}

private:

};

#endif  // IACT_VISUAL_VisualObjectManager_H_
