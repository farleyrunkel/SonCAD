// Copyright [2024] SunCAD

#ifndef SRC_IACT_VISUAL_VISUALOBJECT_H_
#define SRC_IACT_VISUAL_VISUALOBJECT_H_

#include <QObject>

#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>

#include "Core/Topology/InteractiveEntity.h"

class WorkspaceController;

class VisualObject : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool Selectable READ IsSelectable WRITE SetIsSelectable)
    Q_PROPERTY(bool Selected READ IsSelected WRITE SetIsSelected)
    Q_PROPERTY(QObject* Tag READ Tag WRITE SetTag)

protected:
    explicit VisualObject(WorkspaceController* workspaceController, InteractiveEntity* entity);

    virtual ~VisualObject() {}

public:
    virtual void Remove() = 0;
    virtual void Update() = 0;

    virtual Handle(AIS_InteractiveObject) AisObject() const = 0;

    WorkspaceController* workspaceController() const;
    Handle(AIS_InteractiveContext) AisContext() const;

    InteractiveEntity* Entity() const { return _Entity; }
    void SetLocalTransformation(const gp_Trsf& transformation);

public:
    virtual bool IsSelectable() const { return false; }
    virtual void SetIsSelectable(bool value) { Q_UNUSED(value); }
    bool IsSelected() const;
    void SetIsSelected(bool value);
    QObject* Tag() const { return _Tag; }
    void SetTag(QObject* tag) { _Tag = tag; }

signals:
    void AisObjectChanged(VisualObject* visualObject);

private:
    WorkspaceController* _WorkspaceController;  // Weak reference
    InteractiveEntity* _Entity;  // Weak reference
    QObject* _Tag = nullptr;  // Tag for additional data
};

#endif  // SRC_IACT_VISUAL_VISUALOBJECT_H_
