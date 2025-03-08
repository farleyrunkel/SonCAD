#include "Iact/Workspace/ModelController.h"

#include "Iact/Workspace/InteractiveContext.h"

std::shared_ptr<Document> DocumentController::newModel()
{
	auto doc = std::make_shared<Document>();
	InteractiveContext::current()->setDocument(doc);
	return doc;
}
