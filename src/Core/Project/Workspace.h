#ifndef _Workspace_h_
#define _Workspace_h_

#include <memory>
#include <vector>

#include <boost/signals2.hpp>

#include <AIS_InteractiveContext.hxx>
#include <AIS_TypeOfPlane.hxx>
#include <gp.hxx>
#include <gp_Mat.hxx>
#include <gp_Pln.hxx>
#include <gp_Quaternion.hxx>
#include <NCollection_Vector.hxx>
#include <V3d_Viewer.hxx>

// Forward declaire
class WorkingContext;
class Document;
class Viewport;

class Workspace : public std::enable_shared_from_this<Workspace>
{
public:
	enum GridTypes
	{
		Rectangular,
		Circular
	};

public:
	explicit Workspace(const std::shared_ptr<Document>& theDoc);

public:
	//! Getter and Setter

	Handle(V3d_Viewer) GetViewer() const { return myViewer; }

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

	std::shared_ptr<WorkingContext> GetGlobalWorkingContext() const { return myGlobalWorkingContext; }
	void SetGlobalWorkingContext(const std::shared_ptr<WorkingContext>& theValue) { myGlobalWorkingContext = theValue; }

	std::shared_ptr<WorkingContext> GetCurrentWorkingContext() const { return myCurrentWorkingContext; }
	void SetCurrentWorkingContext(const std::shared_ptr<WorkingContext>& theValue) { myCurrentWorkingContext = theValue; }

	std::weak_ptr<Document> document() const { return myDocument; }
	void SetDocument(const std::shared_ptr<Document>& theValue) { myDocument = theValue; }

public:
	void InitV3dViewer();
	void InitAisContext();

	//! Working Plane
	gp_Quaternion GetWorkingPlaneRotation() const;

	void SetDefaultWorkingPlane(AIS_TypeOfPlane type);

	//! compute grid point
	gp_Pnt2d ComputeGridPoint(gp_Pnt2d coord);

	//! project to grid fro screen
	bool ProjectToGrid(const std::shared_ptr<Viewport>& viewport, int screenX, int screenY, gp_Pnt& pnt);

private:
	void ApplyWorkingContext();

public:
	boost::signals2::signal<void(Workspace*)> sig_GridChanged;
	boost::signals2::signal<void(const std::string&)> sig_PropertyChanged;

private:
	std::vector<std::shared_ptr<Viewport>> myViewports;
	std::shared_ptr<Document> myDocument;

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

	std::shared_ptr<WorkingContext> myGlobalWorkingContext;
	std::shared_ptr<WorkingContext> myCurrentWorkingContext;
};

#endif // !_Workspace_h_
