// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALOBJECT_H_
#define IACT_VISUAL_VISUALOBJECT_H_

#include <boost/signals2.hpp>

#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>
#include <Standard_Handle.hxx>

#include "Comm/BaseObject.h"
#include "Core/Topology/InteractiveEntity.h"
#include "Iact/Framework/WorkspaceControl.h"
#include "Iact/Workspace/WorkspaceController.h"

DEFINE_STANDARD_HANDLE(VisualObject, BaseObject);

class VisualObject : public BaseObject
{
protected:
    explicit VisualObject(const Handle(WorkspaceController)& workspaceController, const Handle(InteractiveEntity)& entity);
    virtual ~VisualObject()
    {}

public:
    virtual void Remove() = 0;
    virtual void Update() = 0;

    virtual Handle(AIS_InteractiveObject) AisObject() const = 0;

    Handle(WorkspaceController) GetGetWorkspaceController() const
    {
        return _WorkspaceController;
    }

    Handle(AIS_InteractiveContext) AisContext() const;

    Handle(InteractiveEntity) Entity() const
    {
        return _Entity;
    }

    void SetLocalTransformation(const gp_Trsf& transformation);

    virtual bool IsSelectable() const
    {
        return false;
    }

    virtual void SetIsSelectable(bool value)
    {
        (void)value;
    }

    bool IsSelected() const;
    void SetIsSelected(bool value);

    QVariant Tag() const
    {
        return _Tag;
    }

    void SetTag(const QVariant& tag)
    {
        _Tag = tag;
    }

    // Signal: AIS Object Changed
    boost::signals2::signal<void(const std::shared_ptr<VisualObject>&)> OnAisObjectChanged;

private:
    Handle(WorkspaceController) _WorkspaceController;
    Handle(InteractiveEntity) _Entity;
    QVariant _Tag;
};

#endif  // IACT_VISUAL_VISUALOBJECT_H_
