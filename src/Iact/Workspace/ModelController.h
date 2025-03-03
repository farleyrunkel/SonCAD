#ifndef _ModelController_h
#define _ModelController_h

#include <vector>
#include <string>

#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>

DEFINE_STANDARD_HANDLE(ModelController, Standard_Transient)

class ModelController : public Standard_Transient
{
public:
	explicit ModelController() {}

private:
	const int _MaxMruCount = 12;
	std::vector<std::string> myMruList;
 };

#endif // !_ModelController_h
