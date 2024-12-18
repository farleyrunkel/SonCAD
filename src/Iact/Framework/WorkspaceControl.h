// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
#define SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_

#include <QObject>
#include <QList>

#include <Standard_Handle.hxx>

#include "Iact/HudElements/HudElement.h"
#include "Iact/Workspace/MouseEventData.h"
#include "Iact/Visual/VisualObject.h"


class Sun_WorkspaceController;

class WorkspaceControl : public QObject, public IMouseEventHandler 
{
	Q_OBJECT

 public:
	explicit WorkspaceControl(QObject* parent = nullptr);

	Handle(Sun_WorkspaceController) WorkspaceController() const;
	void setWorkspaceController(const Handle(Sun_WorkspaceController)& WorkspaceController);

 protected:
    virtual QList<WorkspaceControl*> GetChildren() const;
    virtual void Cleanup() {}

    void SetHintMessage(const QString& message);

    void Add(Sun_VisualObject* visual);
    void Add(IHudElement* hudElement);

    // Assuming cleanup and cleanedUp are functions from the base class
    void cleanup() {
        // Resource cleanup implementation
    }

 public:
    virtual bool onMouseMove(MouseEventData* data) override {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) { 
                return child->onMouseMove(data);
            });
    }

    virtual bool onMouseDown(MouseEventData* data) override {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) {
                return child->onMouseDown(data); });
    }

    virtual bool onMouseUp(MouseEventData* data) override {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) {
                return child->onMouseUp(data); });
    }

    virtual void enrichContextMenu(QList<QAction*>& itemList) {
        auto children = GetChildren();
        std::for_each(children.begin(), children.end(),
            [&itemList](WorkspaceControl* child) { child->enrichContextMenu(itemList); });
    }

    virtual bool onKeyPressed(MouseEventData* data) {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
            [data](WorkspaceControl* child) {
               return child->onKeyPressed(data); });
    }

 private:
    Handle(Sun_WorkspaceController) _WorkspaceController;
	QList<IHudElement*> _HudElements;
    QList<Sun_VisualObject*> _VisualObjects;

};

#endif  // SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
