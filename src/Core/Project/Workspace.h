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

	void initViewport();

public:
	//! Getter and Setter

	Handle(V3d_Viewer) getViewer() const { return m_Viewer; }

	bool getGridEnabled() const { return m_GridEnabled; }
	void setGridEnabled(bool theValue) { m_GridEnabled = theValue; }

	GridTypes getGridType() const { return m_GridType; }
	void setGridType(GridTypes theValue) { m_GridType = theValue; }

	double getGridStep() const { return m_GridStep; }
	void setGridStep(double theValue) { m_GridStep = theValue; }

	double getGridRotation() const { return m_GridRotation; }
	void setGridRotation(double theValue) { m_GridRotation = theValue; }

	int getGridDivisions() const { return m_GridDivisions; }
	void setGridDivisions(int theValue) { m_GridDivisions = theValue; }

	const gp_Pln& getWorkingPlane() const { return m_WorkingPlane; }
	void setWorkingPlane(const gp_Pln& theValue) { m_WorkingPlane = theValue; }

	std::shared_ptr<WorkingContext> getGlobalWorkingContext() const { return m_GlobalWorkingContext; }
	void setGlobalWorkingContext(const std::shared_ptr<WorkingContext>& theValue) { m_GlobalWorkingContext = theValue; }

	std::shared_ptr<WorkingContext> getCurrentWorkingContext() const { return m_CurrentWorkingContext; }
	void setCurrentWorkingContext(const std::shared_ptr<WorkingContext>& theValue) { m_CurrentWorkingContext = theValue; }

	std::weak_ptr<Document> document() const { return m_Document; }
	void setDocument(const std::shared_ptr<Document>& theValue) { m_Document = theValue; }

	std::vector<std::shared_ptr<Viewport>>& viewports() { return m_Viewports; }

public:
	void initV3dViewer();
	void initAisContext();

	//! Working Plane
	gp_Quaternion getWorkingPlaneRotation() const;

	void setDefaultWorkingPlane(AIS_TypeOfPlane type);

	//! compute grid point
	gp_Pnt2d computeGridPoint(const gp_Pnt2d& coord);

	//! project to grid fro screen
	bool projectToGrid(const std::shared_ptr<Viewport>& viewport, int screenX, int screenY, gp_Pnt& pnt);

private:
	void applyWorkingContext();

public:
	boost::signals2::signal<void(Workspace*)> sig_GridChanged;
	boost::signals2::signal<void(const std::string&)> sig_PropertyChanged;

private:
	std::vector<std::shared_ptr<Viewport>> m_Viewports;
	std::shared_ptr<Document> m_Document;

	Handle(V3d_Viewer) m_Viewer;
	Handle(AIS_InteractiveContext) m_Context;

	bool m_NeedsRedraw;
	bool m_NeedsImmediateRedraw;
	bool m_GridEnabled;

	GridTypes m_GridType;
	double m_GridStep;
	double m_GridRotation;
	int m_GridDivisions;

	gp_Pln m_WorkingPlane;

	std::shared_ptr<WorkingContext> m_GlobalWorkingContext;
	std::shared_ptr<WorkingContext> m_CurrentWorkingContext;
};

#endif // !_Workspace_h_
