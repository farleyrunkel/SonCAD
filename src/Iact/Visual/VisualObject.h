// Copyright [2024] SunCAD

#ifndef SRC_IACT_VISUAL_VISUALOBJECT_H_
#define SRC_IACT_VISUAL_VISUALOBJECT_H_

#include <QObject>

#include "Iact/Workspace/WorkspaceController.h"
#include "Core/Topology/InteractiveEntity.h"

class VisualObject : public QObject {
    Q_OBJECT

public:
    explicit VisualObject(WorkspaceController* workspaceController, InteractiveEntity* entity, QObject* parent = nullptr)
        : QObject(parent), m_workspaceController(workspaceController), m_entity(entity) {}

    virtual ~VisualObject() {}

    //--------------------------------------------------------------------------------------------------

    WorkspaceController* workspaceController() const { return m_workspaceController; }

    //--------------------------------------------------------------------------------------------------

    Handle(AIS_InteractiveContext) aisContext() const { return m_workspaceController->workspace()->aisContext(); }

    //--------------------------------------------------------------------------------------------------

    virtual Handle(AIS_InteractiveObject) aisObject() const = 0;

    //--------------------------------------------------------------------------------------------------

    virtual bool isSelectable() const { return false; }

    void setIsSelectable(bool value) { Q_UNUSED(value); }

    //--------------------------------------------------------------------------------------------------

    bool isSelected() const {
        return aisContext()->IsSelected(aisObject());
    }

    void setIsSelected(bool value) {
        if (aisContext()->IsSelected(aisObject()) != value) {
            aisContext()->AddOrRemoveSelected(aisObject(), false);
        }
    }

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
