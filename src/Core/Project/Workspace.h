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

// Forward declarations
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
    ~Workspace(); // Added destructor for cleanup

    void initViewport();

    Handle(AIS_InteractiveContext) aisContext() const;
    Handle(V3d_Viewer) v3dViewer() const { return m_Viewer; }

public:
    // Getters and Setters
    Handle(V3d_Viewer) getViewer() const { return m_Viewer; }

    bool gridEnabled() const { return m_GridEnabled; }
    void setGridEnabled(bool theValue);

    GridTypes getGridType() const { return m_GridType; }
    void setGridType(GridTypes theValue);

    double getGridStep() const { return m_GridStep; }
    void setGridStep(double theValue);

    double getGridRotation() const { return m_GridRotation; }
    void setGridRotation(double theValue);

    int getGridDivisions() const { return m_GridDivisions; }
    void setGridDivisions(int theValue);

    const gp_Pln& getWorkingPlane() const { return m_WorkingPlane; }
    void setWorkingPlane(const gp_Pln& theValue);

    std::shared_ptr<WorkingContext> getGlobalWorkingContext() const { return m_GlobalWorkingContext; }

    std::shared_ptr<WorkingContext> workingContext() const { return m_CurrentWorkingContext; }

    std::weak_ptr<Document> document() const { return m_Document; }

    std::vector<std::shared_ptr<Viewport>>& viewports() { return m_Viewports; }

    // needsRedraw
	bool needsRedraw() const { return m_NeedsRedraw; }
	void setNeedsRedraw(bool theValue) { m_NeedsRedraw = theValue; }

	// needsImmediateRedraw
	bool needsImmediateRedraw() const { return m_NeedsImmediateRedraw; }
	void setNeedsImmediateRedraw(bool theValue) { m_NeedsImmediateRedraw = theValue; }

public:
    void initV3dViewer();
    void initAisContext();

    // Working Plane
    gp_Quaternion getWorkingPlaneRotation() const;
    void setDefaultWorkingPlane(AIS_TypeOfPlane type);

    // Grid Computations
    gp_Pnt2d computeGridPoint(const gp_Pnt2d& coord);
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
    Handle(AIS_InteractiveContext) m_context;

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