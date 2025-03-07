// Copyright [2024] SunCAD

#ifndef APP_VIEWPORTPANELMODEL_H_
#define APP_VIEWPORTPANELMODEL_H_

// stl includes
#include <any>

// Project includes
#include "Comm/BaseObject.h"
#include "Comm/ObservableCollection.h"
#include "Comm/PropertyChangedEventArgs.h"
#include "Iact/HudElements/HudElement.h"
#include "Iact/HudElements/HudManager.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"

class ViewportPanelModel : public BaseObject, public HudManager
{
public:
	ViewportPanelModel();

    virtual void addElement(HudElement* element) override;

    virtual void removeElement(HudElement* element) override;
    virtual void removeElements(std::function<bool(HudElement*)> predicate) override;

    // virtual void SetCursor(QObject* owner, Cursor* cursor) override {}
    virtual void setHintMessage(const QString& message) override;

    QString hintMessage();

    WorkspaceController* workspaceController() const 
    {
        return m_workspaceController;
    }

    // ViewportController getter/setter
    ViewportController* viewportController() const 
    {
        return m_viewportController;
    }

    void setViewportController(ViewportController* value);

    // workspaceController getter/setter
    void setWorkspaceController(WorkspaceController* value);

    void context_PropertyChanged(const QString& propertyName);
//
//signals: 
//    void hudElementAdded(HudElement*);
//    void hudElementsRemoved(HudElement*);

private:
    WorkspaceController* m_workspaceController;
    ViewportController* m_viewportController;
    QList<HudElement*> m_hudElements;
    QString m_hintMessage;
};

#endif  // APP_VIEWPORTPANELMODEL_H_
