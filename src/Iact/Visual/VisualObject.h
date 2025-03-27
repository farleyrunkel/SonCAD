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
    explicit VisualObject(const Handle(WorkspaceController)& workspaceController,
                          const Handle(InteractiveEntity)& entity);
    virtual ~VisualObject()
    {}

public:
    Handle(WorkspaceController) GetWorkspaceController() const;

    Handle(AIS_InteractiveContext) AisContext() const;

    virtual Handle(AIS_InteractiveObject) AisObject() const = 0;

    virtual bool IsSelectable() const;
    virtual void SetIsSelectable(bool value);

    bool IsSelected() const;
    void SetIsSelected(bool value);


    std::any Tag() const;

    void SetTag(const std::any& tag);

    Handle(InteractiveEntity) Entity() const;

    virtual void Remove() = 0;
    virtual void Update() = 0;

    void SetLocalTransformation(const gp_Trsf& transformation);

public:
    boost::signals2::signal<void(const Handle(VisualObject)&)> AisObjectChanged;

protected:
    void RaiseAisObjectChanged()
    {
        AisObjectChanged(this);
    }

private:
    Handle(WorkspaceController) _WorkspaceController;
    Handle(InteractiveEntity) _Entity;
    std::any _Tag;
};

#endif  // IACT_VISUAL_VISUALOBJECT_H_
