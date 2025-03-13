// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALSHAPE_H_
#define IACT_VISUAL_VISUALSHAPE_H_

// stl include
#include <functional>

// Occt includes
#include <AIS_InteractiveObject.hxx>
#include <AIS_Shape.hxx>
#include <Prs3d_Drawer.hxx>
#include <TopoDS_Shape.hxx>

// Project includes
#include "Core/Topology/InteractiveEntity.h"
#include "Core/Topology/Layer.h"
#include "Iact/Visual/Marker.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Visual/VisualObjectManager.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Occt/AisExtensions/AISX_Guid.h"

class VisualShape : public VisualObject
{

public:
    enum Options
    {
        None,
        Ghosting = 1 << 0,   // Used to visualize a normally hidden object
    };

    class AttributeSet
    {
    public:
        AttributeSet()
        {
            m_drawer = new Prs3d_Drawer();
            m_drawer->SetupOwnDefaults();
        }

        Handle(Prs3d_Drawer) drawer() const
        {
            return m_drawer;
        }

    private:
        Handle(Prs3d_Drawer) m_drawer;
    };

public:
    explicit VisualShape(const std::shared_ptr<WorkspaceController>& workspaceController,
                         const std::shared_ptr<InteractiveEntity>& entity, 
                         Options options = None)
        : VisualObject(workspaceController, nullptr)
    {}
    virtual ~VisualShape() {}
};

#endif  // IACT_VISUAL_VISUALSHAPE_H_
