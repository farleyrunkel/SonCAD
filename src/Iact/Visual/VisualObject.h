// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALOBJECT_H_
#define IACT_VISUAL_VISUALOBJECT_H_

// Standard includes
#include <memory>

// Boost includes
#include <boost/signals2.hpp>

// OCCT includes
#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>

// Project includes
#include "Core/Topology/InteractiveEntity.h"

// Forward declarations
class WorkspaceController;

class VisualObject
{
public:
    using Ptr = std::shared_ptr<VisualObject>;

protected:
    explicit VisualObject(std::shared_ptr<WorkspaceController> workspaceController,
                          std::shared_ptr<InteractiveEntity> entity);
    virtual ~VisualObject() = default;

public:
    virtual void remove() = 0;
    virtual void update() = 0;
    virtual Handle(AIS_InteractiveObject) aisObject() const = 0;

    std::shared_ptr<WorkspaceController> workspaceController() const;
    Handle(AIS_InteractiveContext) aisContext() const;

    std::shared_ptr<InteractiveEntity> entity() const
    {
        return m_entity;
    }
    void setLocalTransformation(const gp_Trsf& transformation);

public:
    virtual bool isSelectable() const
    {
        return false;
    }
    virtual void setIsSelectable(bool /*value*/)
    {
        // Default no-op
    }
    bool isSelected() const;
    void setIsSelected(bool value);


public: // Signals
    boost::signals2::signal<void(VisualObject*)> aisObjectChanged;

private:
    std::shared_ptr<WorkspaceController> m_workspaceController;
    std::shared_ptr<InteractiveEntity> m_entity;
};

#endif  // IACT_VISUAL_VISUALOBJECT_H_
