#ifndef _WorkingContext_H_
#define _WorkingContext_H_

#include <gp.hxx>
#include <gp_Pln.hxx>
#include <Standard_Transient.hxx>

#include "Core/Project/Workspace.h"

DEFINE_STANDARD_HANDLE(WorkingContext, Standard_Transient)

class WorkingContext final : public Standard_Transient
{
public:
	explicit WorkingContext() 
		: myGridType(Workspace::GridTypes::Rectangular)
		, myGridStep(1.0)
		, myGridRotation(0.0)
		, myGridDivisions(8)
		, myWorkingPlane(gp_Pln(gp::XOY()))
	{}

	gp_Pln GetWorkingPlane() const { return myWorkingPlane; }
	void SetWorkingPlane(const gp_Pln& thePlane) { myWorkingPlane = thePlane; }

	Workspace::GridTypes GetGridType() const { return myGridType; }
	void SetGridType(Workspace::GridTypes theType) { myGridType = theType; }

	double GetGridStep() const { return myGridStep; }
	void SetGridStep(double theStep) { myGridStep = theStep; }

	double GetGridRotation() const { return myGridRotation; }
	void SetGridRotation(double theRotation) { myGridRotation = theRotation; }

	int GetGridDivisions() const { return myGridDivisions; }
	void SetGridDivisions(int theDivisions) { myGridDivisions = theDivisions; }

private:
	gp_Pln myWorkingPlane;
	Workspace::GridTypes myGridType;
	double myGridStep;
	double myGridRotation;
	int myGridDivisions;
};

#endif // !_WorkingContext_H_
