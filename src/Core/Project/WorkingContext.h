#ifndef _WorkingContext_h_
#define _WorkingContext_h_

#include <gp_Pln.hxx>
#include <Standard_Transient.hxx>

#include "Core/Project/Workspace.h"
#include "Core/Project/Document.h"

DEFINE_STANDARD_HANDLE(WorkingContext, Standard_Transient)

class WorkingContext final : public Standard_Transient
{
public:
	explicit WorkingContext() {}

private:

	gp_Pln myWorkingPlane;

	Workspace::GridTypes myGridType;
	double myGridStep;
	double myGridRotation;
	int myGridDivisions;
};

#endif // !_WorkingContext_h_
