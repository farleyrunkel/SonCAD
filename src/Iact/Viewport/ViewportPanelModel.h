// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTPANELMODEL_H_
#define APP_VIEWPORTPANELMODEL_H_

// stl includes
#include <any>

// Project includes
#include "Comm/ObservableCollection.h"
#include "Comm/PropertyChangedEventArgs.h"
#include "Comm/PropertySignal.h"
#include "Iact/HudElements/HudElement.h"
#include "Iact/HudElements/HudManager.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"

class ViewportPanelModel : public HudManager, public enable_property_changed_signal
{
public:
	ViewportPanelModel();

    virtual void addElement(HudElement* element) override;

    virtual void removeElement(HudElement* element) override;
    virtual void removeElements(std::function<bool(HudElement*)> predicate) override;

    // virtual void SetCursor(QObject* owner, Cursor* cursor) override {}
    virtual void setHintMessage(const QString& message) override;

    QString hintMessage();

    std::shared_ptr<WorkspaceController> workspaceController() const
    {
        return m_workspaceController;
    }

    // ViewportController getter/setter
    std::shared_ptr<ViewportController> viewportController() const 
    {
        return m_viewportController;
    }

    void setViewportController(const std::shared_ptr<ViewportController>& value);

    // workspaceController getter/setter
    void setWorkspaceController(const std::shared_ptr<WorkspaceController>& value);

    void context_PropertyChanged(const std::string& propertyName);
//
//signals: 
//    void hudElementAdded(HudElement*);
//    void hudElementsRemoved(HudElement*);

private:
    std::shared_ptr<WorkspaceController> m_workspaceController;
    std::shared_ptr<ViewportController> m_viewportController;
    QList<HudElement*> m_hudElements;
    QString m_hintMessage;
};

#endif  // APP_VIEWPORTPANELMODEL_H_
