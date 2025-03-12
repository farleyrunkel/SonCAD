#ifndef _WorkingContext_H_
#define _WorkingContext_H_

#include <gp.hxx>
#include <gp_Pln.hxx>
 

#include "Core/Project/Workspace.h"

class WorkingContext
{
public:
	explicit WorkingContext() 
		: m_WorkingPlane(gp_Pln(gp::XOY()))
		, m_GridType(Workspace::GridTypes::Rectangular)
		, m_GridStep(1.0)
		, m_GridRotation(0.0)
		, m_GridDivisions(8)
		
	{}

	gp_Pln workingPlane() const { return m_WorkingPlane; }
	void SetWorkingPlane(const gp_Pln& thePlane) { m_WorkingPlane = thePlane; }

	Workspace::GridTypes gridType() const { return m_GridType; }
	void SetGridType(Workspace::GridTypes theType) { m_GridType = theType; }

	double gridStep() const { return m_GridStep; }
	void SetGridStep(double theStep) { m_GridStep = theStep; }

	double gridRotation() const { return m_GridRotation; }
	void SetGridRotation(double theRotation) { m_GridRotation = theRotation; }

	int gridDivisions() const { return m_GridDivisions; }
	void SetGridDivisions(int theDivisions) { m_GridDivisions = theDivisions; }

private:
	gp_Pln m_WorkingPlane;
	Workspace::GridTypes m_GridType;
	double m_GridStep;
	double m_GridRotation;
	int m_GridDivisions;
};

#endif // !_WorkingContext_H_
