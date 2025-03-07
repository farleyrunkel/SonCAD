#include "Iact/Workspace/InteractiveContext.h"

#include "Iact/Workspace/ModelController.h"


InteractiveContext* InteractiveContext::m_current = nullptr;

InteractiveContext::InteractiveContext() {
	m_current = this;
	m_modelController = std::make_shared<DocumentController>();
}
