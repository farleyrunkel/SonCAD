#ifndef _Workspace_h_
#define _Workspace_h_

#include <vector>

#include <boost/signals2.hpp>

#include <AIS_InteractiveContext.hxx>
#include <gp_Pln.hxx>
#include <Standard_Transient.hxx>
#include <V3d_Viewer.hxx>
#include <gp_Quaternion.hxx>
#include <gp_Mat.hxx>
#include <AIS_TypeOfPlane.hxx>
#include <gp.hxx>

// Forward declaire
class WorkingContext;
class Document;
class Viewport;

DEFINE_STANDARD_HANDLE(Workspace, Standard_Transient)

class Workspace final : public Standard_Transient
{
	using GridChangedSignal = boost::signals2::signal<void(Workspace*)>;
	using PropertyChangedSignal = boost::signals2::signal<void(const std::string&)>;

public:
	enum GridTypes
	{
		Rectangular,
		Circular
	};

public:
	explicit Workspace(const Handle(Document)& theDoc);

public:
	//! Getter and Setter

	bool GetGridEnabled() const { return myGridEnabled; }
	void SetGridEnabled(bool theValue) { myGridEnabled = theValue; }

	GridTypes GetGridType() const { return myGridType; }
	void SetGridType(GridTypes theValue) { myGridType = theValue; }

	double GetGridStep() const { return myGridStep; }
	void SetGridStep(double theValue) { myGridStep = theValue; }

	double GetGridRotation() const { return myGridRotation; }
	void SetGridRotation(double theValue) { myGridRotation = theValue; }

	int GetGridDivisions() const { return myGridDivisions; }
	void SetGridDivisions(int theValue) { myGridDivisions = theValue; }

	const gp_Pln& GetWorkingPlane() const { return myWorkingPlane; }
	void SetWorkingPlane(const gp_Pln& theValue) { myWorkingPlane = theValue; }

	Handle(WorkingContext) GetGlobalWorkingContext() const { return myGlobalWorkingContext; }
	void SetGlobalWorkingContext(const Handle(WorkingContext)& theValue) { myGlobalWorkingContext = theValue; }

	Handle(WorkingContext) GetCurrentWorkingContext() const { return myCurrentWorkingContext; }
	void SetCurrentWorkingContext(const Handle(WorkingContext)& theValue) { myCurrentWorkingContext = theValue; }

	Handle(Document) GetDocument() const { return myDocument; }
	void SetDocument(const Handle(Document)& theValue) { myDocument = theValue; }

public:
	void InitV3dViewer();
	void InitAisContext();

	//! Working Plane
	gp_Quaternion GetWorkingPlaneRotation() const;

	void SetDefaultWorkingPlane(AIS_TypeOfPlane type);

	//! compute grid point
	gp_Pnt2d ComputeGridPoint(gp_Pnt2d coord);

	//! project to grid fro screen
	bool ProjectToGrid(const Handle(Viewport)& viewport, int screenX, int screenY, gp_Pnt& pnt);
	

public:
	GridChangedSignal& GridChanged()
	{
		return emit_GridChanged;
	}

private:
	void ApplyWorkingContext();

private:
	std::vector<Handle(Viewport)> myViewports;

	Handle(Document) myDocument;
	Handle(V3d_Viewer) myViewer;
	Handle(AIS_InteractiveContext) myContext;

	bool myNeedsRedraw;
	bool myNeedsImmediateRedraw;
	bool myGridEnabled;

	GridTypes myGridType;
	double myGridStep;
	double myGridRotation;
	int myGridDivisions;

	gp_Pln myWorkingPlane;

	Handle(WorkingContext) myGlobalWorkingContext;
	Handle(WorkingContext) myCurrentWorkingContext;

private:
	GridChangedSignal emit_GridChanged;
	PropertyChangedSignal emit_PropertyChanged;
};

#endif // !_Workspace_h_
