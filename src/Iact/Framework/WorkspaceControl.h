// Copyright [2024] SunCAD

#ifndef IACT_FRAMEWORK_WORKSPACECONTROLL_H_
#define IACT_FRAMEWORK_WORKSPACECONTROLL_H_

#include <QList>

#include <Standard_Handle.hxx>

#include "Comm/BaseObject.h"
#include "Iact/HudElements/HudElement.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/MouseEventData.h"

DEFINE_STANDARD_HANDLE(WorkspaceControl, BaseObject);

class WorkspaceControl : public BaseObject, public IMouseEventHandler
{
public:
    explicit WorkspaceControl();

    Handle(WorkspaceController) GetWorkspaceController() const;

    void SetWorkspaceController(const Handle(WorkspaceController)& WorkspaceController);

    virtual void Cleanup()
    {}

protected:
    virtual QList<Handle(WorkspaceControl)> GetChildren() const;

    void SetHintMessage(const QString& message);

    void Add(Handle(VisualObject) visual);

    void Add(IHudElement* hudElement);

public:
    virtual bool OnMouseMove(MouseEventData* data) override
    {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
                           [data](Handle(WorkspaceControl) child)
        {
            return child->OnMouseMove(data);
        });
    }

    virtual bool OnMouseDown(MouseEventData* data) override
    {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
                           [data](Handle(WorkspaceControl) child)
        {
            return child->OnMouseDown(data);
        });
    }

    virtual bool OnMouseUp(MouseEventData* data) override
    {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
                           [data](Handle(WorkspaceControl) child)
        {
            return child->OnMouseUp(data);
        });
    }

    virtual void enrichContextMenu(QList<QAction*>& itemList)
    {
        auto children = GetChildren();
        std::for_each(children.begin(), children.end(),
                      [&itemList](Handle(WorkspaceControl) child)
        {
            child->enrichContextMenu(itemList);
        });
    }

    virtual bool OnKeyPressed(MouseEventData* data)
    {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
                           [data](Handle(WorkspaceControl) child)
        {
            return child->OnKeyPressed(data);
        });
    }

private:
    Handle(WorkspaceController) _WorkspaceController;
    QList<IHudElement*> _HudElements;
    QList<Handle(VisualObject)> _VisualObjects;
};

#endif  // IACT_FRAMEWORK_WORKSPACECONTROLL_H_
