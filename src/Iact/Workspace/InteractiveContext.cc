#include "Iact/Workspace/InteractiveContext.h"

#include "Iact/Workspace/ModelController.h"
#include "Iact/Workspace/WorkspaceController.h"

InteractiveContext* InteractiveContext::m_current = nullptr;

InteractiveContext::InteractiveContext() {
	m_current = this;
	m_modelController = std::make_shared<DocumentController>();
}

InteractiveContext::~InteractiveContext() {}

InteractiveContext* InteractiveContext::current()
{
	return m_current;
}

std::shared_ptr<DocumentController> InteractiveContext::documentController() const
{
	return m_modelController;
}

// protect set document controller
void InteractiveContext::setDocumentController(const std::shared_ptr<DocumentController>& value)
{
	m_modelController = value;
}

std::shared_ptr<WorkspaceController> InteractiveContext::workspaceController() const
{
	return m_workspaceController;
}

std::shared_ptr<ViewportController> InteractiveContext::viewportController() const
{
	return m_viewportController;
}

void InteractiveContext::setWorkspace(const std::shared_ptr<Workspace>& value)
{
	if(CoreContext::workspace() == value)
	{
		return;
	}
	m_workspaceController.reset();
	if(value)
	{
		m_workspaceController = std::make_shared<WorkspaceController>(value);
		m_workspaceController->initWorkspace();
	}

	CoreContext::setWorkspace(value);
	raisePropertyChanged("workspaceController");
}

void InteractiveContext::setViewport(const std::shared_ptr<Viewport>& value)
{
	CoreContext::setViewport(value);
	if(value == nullptr)
	{
		m_viewportController.reset();
		m_workspaceController->setActiveViewport(nullptr);
	}
	else
	{
		m_workspaceController->setActiveViewport(value);
		m_viewportController = m_workspaceController->getViewController(value);
		raisePropertyChanged("viewportController");
	}
}
