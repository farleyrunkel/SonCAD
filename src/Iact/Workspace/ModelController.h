#ifndef _ModelController_h
#define _ModelController_h

#include <vector>
#include <string>

#include <Standard_Handle.hxx>
 
#include "Comm/BaseObject.h"

class ModelController : public enable_property_changed_signal
{
public:
	explicit ModelController() {}

	bool askForSavingModelChanges() { return true;}

	void newModel() {}

private:
	const int myMaxMruCount = 12;
	std::vector<std::string> myMruList;
 };

#endif // !_ModelController_h
