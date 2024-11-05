// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
#define SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_

#include <QObject>
#include <QVector>
#include <QList>
#include "Iact/HudElements/HudElement.h"
#include "Iact/Workspace/MouseEventData.h"

class WorkspaceController;

class WorkspaceControl : public QObject, public IMouseEventHandler {
	Q_OBJECT

 public:
	explicit WorkspaceControl(QObject* parent = nullptr);

	WorkspaceController* workspaceController() const;
	void setWorkspaceController(WorkspaceController* workspaceController);

 protected:
    virtual QList<WorkspaceControl*> GetChildren() const;

 public:
    virtual bool OnMouseMove(QMouseEvent* event) {
        return std::any_of(GetChildren().begin(), GetChildren().end(),
            [event](WorkspaceControl* child) { return child->OnMouseMove(event); });
    }

    virtual bool OnMouseDown(QMouseEvent* event) {
        return std::any_of(GetChildren().begin(), GetChildren().end(),
            [event](WorkspaceControl* child) { return child->OnMouseDown(event); });
    }

    virtual bool OnMouseUp(QMouseEvent* event) {
        return std::any_of(GetChildren().begin(), GetChildren().end(),
            [event](WorkspaceControl* child) { return child->OnMouseUp(event); });
    }

    virtual void EnrichContextMenu(QList<QAction*>& itemList) {
        std::for_each(GetChildren().begin(), GetChildren().end(),
            [&itemList](WorkspaceControl* child) { child->EnrichContextMenu(itemList); });
    }

    virtual bool OnKeyPressed(QKeyEvent* event) {
        return std::any_of(GetChildren().begin(), GetChildren().end(),
            [event](WorkspaceControl* child) { return child->OnKeyPressed(event); });
    }

 private: 
	WorkspaceController* m_workspaceController;
	QVector<HudElement*> m_hudElements;

};

#endif  // SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
