// Copyright [2024] SunCAD

#include "Iact/Viewport/ViewportPanelModel.h"

#include <boost/signals2.hpp>

ViewportPanelModel::ViewportPanelModel()
{
    //Entity.ErrorStateChanged += _Entity_ErrorStateChanged;

	InteractiveContext::current()->propertyChanged.connect(
        std::bind(&ViewportPanelModel::context_PropertyChanged, this, std::placeholders::_1)
    );

    setWorkspaceController(InteractiveContext::current()->workspaceController());
    setViewportController(InteractiveContext::current()->viewportController());
}

void ViewportPanelModel::addElement(HudElement* element) 
{
    if (m_hudElements.contains(element)) {
        return;
    }

    //element->setWorkspaceController(m_workspaceController);
    //element->initialize();
    m_hudElements.append(element);
    //emit hudElementAdded(element);
}

void ViewportPanelModel::removeElement(HudElement* element) 
{
	if (m_hudElements.contains(element)) {
		m_hudElements.removeAll(element);
        element->deleteLater();
		//emit hudElementsRemoved(element);
	}
}

void ViewportPanelModel::removeElements(std::function<bool(HudElement*)> predicate) 
{
	for (int i = m_hudElements.size() - 1; i >= 0; i--) {
		if (predicate(m_hudElements[i])) {
			removeElement(m_hudElements[i]);
		}
	}
}

// virtual void SetCursor(QObject* owner, Cursor* cursor) override {}

void ViewportPanelModel::setHintMessage(const QString& message) 
{
    m_hintMessage = message;
    raisePropertyChanged("hintMessage");
}

QString ViewportPanelModel::hintMessage() 
{
    return m_hintMessage;
}

void ViewportPanelModel::setViewportController(const std::shared_ptr<ViewportController>& value)
{
    m_viewportController = value;
    raisePropertyChanged("viewportController");
}

void ViewportPanelModel::setWorkspaceController(const std::shared_ptr<WorkspaceController>& value)
{
    if (m_workspaceController != value) {
        m_workspaceController = value;
        if (m_workspaceController != nullptr) {
            //m_workspaceController->setHudManager(this);
        }
        else {
            //HudElements.Clear();
        }
        m_workspaceController = value;
        raisePropertyChanged("workspaceController");
    }
}

void ViewportPanelModel::context_PropertyChanged(const std::string& propertyName) 
{
    auto context = InteractiveContext::current();
    if (propertyName == "workspaceController") {
        if (m_workspaceController != nullptr) {
            //m_workspaceController.Selection.SelectionChanged -= _Selection_SelectionChanged;
        }
        setWorkspaceController(context->workspaceController());

        if (m_workspaceController != nullptr) {
            //m_workspaceController.Selection.SelectionChanged += _Selection_SelectionChanged;
        }
    }
    else if (propertyName == "viewportController") {
        setViewportController(context->viewportController());      
    }
}
