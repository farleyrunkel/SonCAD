// Copyright [2024] SunCAD

#ifndef IACT_FRAMEWORK_WORKSPACECONTROLL_H_
#define IACT_FRAMEWORK_WORKSPACECONTROLL_H_

#include <QList>

#include <Standard_Handle.hxx>
#include <NCollection_Vector.hxx>

#include "Comm/BaseObject.h"
#include "Iact/Workspace/MouseEventData.h"

class WorkspaceController;
class IHudElement;
class VisualObject;

DEFINE_STANDARD_HANDLE(WorkspaceControl, BaseObject);

class WorkspaceControl : public BaseObject
{
public:
    explicit WorkspaceControl();

    Handle(WorkspaceController) GetWorkspaceController() const;

    void SetWorkspaceController(const Handle(WorkspaceController)& WorkspaceController);

    virtual void Cleanup()
    {}

protected:
    virtual NCollection_Vector<Handle(WorkspaceControl)> GetChildren() const;

    void SetHintMessage(const QString& message);

    void Add(Handle(VisualObject) visual);

    void Add(IHudElement* hudElement);

public:
    virtual bool OnMouseMove(const std::shared_ptr<MouseEventData>& data)
    {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
                           [data](Handle(WorkspaceControl) child)
        {
            return child->OnMouseMove(data);
        });
    }

    virtual bool OnMouseDown(const std::shared_ptr<MouseEventData>& data)
    {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
                           [data](Handle(WorkspaceControl) child)
        {
            return child->OnMouseDown(data);
        });
    }

    virtual bool OnMouseUp(const std::shared_ptr<MouseEventData>& data)
    {
        auto children = GetChildren();
        return std::any_of(children.begin(), children.end(),
                           [data](Handle(WorkspaceControl) child)
        {
            return child->OnMouseUp(data);
        });
    }

    virtual void EnrichContextMenu(QList<QAction*>& itemList)
    {
        auto children = GetChildren();
        std::for_each(children.begin(), children.end(),
                      [&itemList](Handle(WorkspaceControl) child)
        {
            child->EnrichContextMenu(itemList);
        });
    }

    virtual bool OnKeyPressed(const std::shared_ptr<MouseEventData>& data)
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
    std::vector<IHudElement*> _HudElements;
    std::vector<Handle(VisualObject)> _VisualObjects;
};

#endif  // IACT_FRAMEWORK_WORKSPACECONTROLL_H_
