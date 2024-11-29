// Copyright [2024] SunCAD

#ifndef SRC_IACT_VISUAL_VISUALOBJECT_H_
#define SRC_IACT_VISUAL_VISUALOBJECT_H_

// Qt includes
#include <QObject>
#include <QSharedPointer>
#include <QVariant>

// Occt includes
#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>
#include <Standard_Handle.hxx>

// SunCAD includes
#include "Core/Topology/InteractiveEntity.h"
#include "Comm/BaseObject.h"

class Sun_WorkspaceController;

DEFINE_STANDARD_HANDLE(Sun_VisualObject, Standard_Transient);

class Sun_VisualObject : public Sun_BaseObject
{
    Q_OBJECT
    Q_PROPERTY(bool Selectable READ IsSelectable WRITE SetIsSelectable)
    Q_PROPERTY(bool Selected READ IsSelected WRITE SetIsSelected)
    Q_PROPERTY(QVariant Tag READ Tag WRITE SetTag)

protected:
    explicit Sun_VisualObject(const Handle(Sun_WorkspaceController)& WorkspaceController, Sun_InteractiveEntity* entity);
    virtual ~Sun_VisualObject() {}

public:
    virtual void Remove() = 0;
    virtual void Update() = 0;

    virtual Handle(AIS_InteractiveObject) AisObject() const = 0;

    Handle(Sun_WorkspaceController) WorkspaceController() const;

    Handle(AIS_InteractiveContext) AisContext() const;

    Sun_InteractiveEntity* Sun_Entity() const { return _Entity; }
    void SetLocalTransformation(const gp_Trsf& transformation);

public:
    virtual bool IsSelectable() const { return false; }
    virtual void SetIsSelectable(bool value) { Q_UNUSED(value); }
    bool IsSelected() const;
    void SetIsSelected(bool value);
    QVariant Tag() const { return _Tag; }
    void SetTag(const QVariant& tag) { _Tag = tag; }

signals:
    void AisObjectChanged(const QSharedPointer<Sun_VisualObject>& visualObject);

private:
    const Handle(Sun_WorkspaceController)& _WorkspaceController;
    Sun_InteractiveEntity* _Entity;
    QVariant _Tag;
};

#endif  // SRC_IACT_VISUAL_VISUALOBJECT_H_
