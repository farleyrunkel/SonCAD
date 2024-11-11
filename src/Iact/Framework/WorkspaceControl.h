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
    virtual QList<WorkspaceControl*> getChildren() const;
    void add(HudElement* hudElement);

 public:
    virtual bool onMouseMove(MouseEventData* data) {
        auto children = getChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) { 
                auto a = child;
                return child->onMouseMove(data); 
            });
    }

    virtual bool onMouseDown(MouseEventData* data) {
        auto children = getChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) {
                auto a = child; return child->onMouseDown(data); });
    }

    virtual bool onMouseUp(MouseEventData* data) {
        auto children = getChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) {
                auto a = child; return child->onMouseUp(data); });
    }

    virtual void enrichContextMenu(QList<QAction*>& itemList) {
        auto children = getChildren();
        std::for_each(children.begin(), children.end(),
            [&itemList](WorkspaceControl* child) { child->enrichContextMenu(itemList); });
    }

    virtual bool onKeyPressed(MouseEventData* data) {
        auto children = getChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) {
                auto a = child; return child->onKeyPressed(data); });
    }

 private: 
	WorkspaceController* m_workspaceController;
	QVector<HudElement*> m_hudElements;
};

#endif  // SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
