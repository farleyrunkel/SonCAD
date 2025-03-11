#ifndef _WorkspaceControl_h
#define _WorkspaceControl_h

#include <memory>
#include <vector>

#include "Iact/Panels/PropertyPanels/PropertyPanel.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/MouseEventData.h"
#include "Iact/Workspace/Snapping/SnapBase.h"

class WorkspaceController;
class HudElement;

class WorkspaceControl
{
public:
	explicit WorkspaceControl();

	// workspaceController
	std::shared_ptr<WorkspaceController> workspaceController() const;
	void setWorkspaceController(const std::shared_ptr<WorkspaceController>& value);

public:
	virtual std::vector<std::shared_ptr<WorkspaceControl>> getChildren() const { return {}; }

	virtual void cleanup() {}

	void setHintMessage(const std::string& message) {}

	void add(const std::shared_ptr<HudElement>& hudElement) {}
	void add(const std::shared_ptr<VisualObject>& visualObject) {}

	void remove(const std::shared_ptr<HudElement>& hudElement) {}
	void setCursor() {}

public:
    virtual bool onMouseMove(const std::shared_ptr<MouseEventData>& data)
    {
        auto children = getChildren();
        return std::any_of(children.begin(), children.end(),
                           [data](const auto& child) {
            return child->onMouseMove(data);
        });
    }

    virtual bool onMouseDown(const std::shared_ptr<MouseEventData>& data)
    {
        auto children = getChildren();
        return std::any_of(children.begin(), children.end(),
                           [data](auto child) {
            return child->onMouseDown(data); });
    }

    virtual bool onMouseUp(const std::shared_ptr<MouseEventData>& data)
    {
        auto children = getChildren();
        return std::any_of(children.begin(), children.end(),
                           [data](auto child) {
            return child->onMouseUp(data); });
    }

    virtual void enrichContextMenu(QList<QAction*>& itemList)
    {
        auto children = getChildren();
        std::for_each(children.begin(), children.end(),
                      [&itemList](auto child) { child->enrichContextMenu(itemList); });
    }

    virtual bool onKeyPressed(const std::shared_ptr<MouseEventData>& data)
    {
        auto children = getChildren();
        return std::any_of(children.begin(), children.end(),
                           [data](auto child) {
            return child->onKeyPressed(data); });
    }

private:
	std::shared_ptr<WorkspaceController> myWorkspaceController;
	bool myPanelsHidden;
	bool myCleanedUp;
	std::vector<std::shared_ptr<HudElement>> myHudElements;
	std::vector<std::shared_ptr<VisualObject>> myVisualObjects;

	std::vector<std::shared_ptr<PropertyPanel>> myPanels;
	std::shared_ptr<SnapBase> mySnap;
};

#endif // !_WorkspaceControl_h
