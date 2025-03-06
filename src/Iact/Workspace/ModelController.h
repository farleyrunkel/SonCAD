#ifndef _ModelController_h
#define _ModelController_h

#include <string>
#include <vector>

#include "Comm/Property.h"
#include "Core/Project/Document.h"

class DocumentController
{
public:
	explicit DocumentController() {}

	bool askForSavingModelChanges() { return true;}

	std::shared_ptr<Document> newModel();

private:
	const int myMaxMruCount = 12;
	std::vector<std::string> myMruList;
 };

#endif // !_ModelController_h
