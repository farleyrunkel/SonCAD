// Copyright [2024] SunCAD

#ifndef SRC_IACT_VISUAL_VISUALOBJECT_H_
#define SRC_IACT_VISUAL_VISUALOBJECT_H_

#include <QObject>

#include <AIS_InteractiveContext.hxx>

#include "Core/Topology/InteractiveEntity.h"

class WorkspaceController;

class VisualObject : public QObject {
    Q_OBJECT

public:
    explicit VisualObject(WorkspaceController* workspaceController, InteractiveEntity* entity, QObject* parent = nullptr);

    virtual ~VisualObject() {}

    //--------------------------------------------------------------------------------------------------

    WorkspaceController* workspaceController() const;

    //--------------------------------------------------------------------------------------------------

    Handle(AIS_InteractiveContext) aisContext() const;

    //--------------------------------------------------------------------------------------------------

    virtual Handle(AIS_InteractiveObject) aisObject() const = 0;

    //--------------------------------------------------------------------------------------------------

    virtual bool isSelectable() const { return false; }

    void setIsSelectable(bool value) { Q_UNUSED(value); }

    //--------------------------------------------------------------------------------------------------

    bool isSelected() const;

    void setIsSelected(bool value);

    //--------------------------------------------------------------------------------------------------

    void setTag(QObject* tag) { Tag = tag; }

    QObject* tag() const { return Tag; }

    //--------------------------------------------------------------------------------------------------

    InteractiveEntity* entity() const { return m_entity; }

    //--------------------------------------------------------------------------------------------------

    virtual void remove() = 0;

    virtual void update() = 0;

    //--------------------------------------------------------------------------------------------------

    //void setLocalTransformation(const Trsf* transformation) {
    //    if (!aisObject()) return;

    //    if (transformation) {
    //        aisObject()->SetLocalTransformation(*transformation);
    //    }
    //    else {
    //        aisObject()->ResetTransformation();
    //    }
    //}

    //--------------------------------------------------------------------------------------------------

signals:
    void aisObjectChanged(VisualObject* visualObject);

protected:
    void raiseAisObjectChanged() {
        emit aisObjectChanged(this);
    }

private:
    WorkspaceController* m_workspaceController;  // Weak reference
    InteractiveEntity* m_entity;  // Weak reference
    QObject* Tag = nullptr;  // Tag for additional data
};

#endif  // SRC_IACT_VISUAL_VISUALOBJECT_H_
