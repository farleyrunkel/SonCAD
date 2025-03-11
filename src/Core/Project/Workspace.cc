#include "Core/Project/Workspace.h"

#include <AIS_InteractiveContext.hxx>
#include <AIS_TypeOfPlane.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <ElSLib.hxx>
#include <gp.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Mat.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Quaternion.hxx>
#include <gp_Trsf2d.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <Prs3d_Drawer.hxx>
#include <Prs3d_LineAspect.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_DirectionalLight.hxx>
#include <V3d_Viewer.hxx>

#include "Core/Project/Viewport.h"
#include "Core/Project/VisualStyles.h"
#include "Core/Project/WorkingContext.h"

Workspace::Workspace(const std::shared_ptr<Document>& theDoc)
    : m_Document(theDoc)
    , m_NeedsRedraw(false)
    , m_NeedsImmediateRedraw(false)
    , m_GridEnabled(true)
    , m_GridType(Rectangular)
    , m_GridStep(10.0)
    , m_GridRotation(0.0)
    , m_GridDivisions(10)
{
    m_GlobalWorkingContext = std::make_shared<WorkingContext>();
    m_CurrentWorkingContext = m_GlobalWorkingContext;
}

Workspace::~Workspace()
{
    m_Viewports.clear(); // Clean up viewports
}

void Workspace::initViewport()
{
    m_Viewports.push_back(std::make_shared<Viewport>(shared_from_this()));
}

Handle(AIS_InteractiveContext) Workspace::aisContext() const
{
    return m_context;
}

void Workspace::initV3dViewer()
{
    if(m_Viewer.IsNull())
    {
        Handle(Aspect_DisplayConnection) aDisp = new Aspect_DisplayConnection();
        Handle(OpenGl_GraphicDriver) aDriver = new OpenGl_GraphicDriver(aDisp);
        aDriver->ChangeOptions().ffpEnable = false;
        aDriver->ChangeOptions().contextDebug = false;

        m_Viewer = new V3d_Viewer(aDriver);
    }

    m_Viewer->SetDefaultViewSize(1000.0);
    m_Viewer->SetDefaultViewProj(V3d_TypeOfOrientation::V3d_XposYposZpos);
    m_Viewer->SetDefaultBackgroundColor(Quantity_Color(NCollection_Vec3{0.3f, 0.3f, 0.3f}));
    m_Viewer->SetDefaultVisualization(V3d_TypeOfVisualization::V3d_ZBUFFER);
    m_Viewer->SetLightOn(new V3d_DirectionalLight(V3d_TypeOfOrientation::V3d_Zneg, Quantity_Color(Quantity_NOC_WHITE), true));
    m_Viewer->SetLightOn(new V3d_AmbientLight(Quantity_Color(Quantity_NOC_WHITE)));

    applyWorkingContext();
}

void Workspace::initAisContext()
{
    if(m_Viewer.IsNull())
    {
        initV3dViewer();
    }

    if(m_context.IsNull())
    {
        m_context = new AIS_InteractiveContext(m_Viewer);
        m_context->UpdateCurrentViewer();
    }

    m_context->SetAutoActivateSelection(true);
    m_context->SetToHilightSelected(false);
    m_context->SetPickingStrategy(SelectMgr_PickingStrategy::SelectMgr_PickingStrategy_OnlyTopmost);
    m_context->SetDisplayMode(AIS_DisplayMode::AIS_Shaded, false);
    m_Viewer->DisplayPrivilegedPlane(false, 1.0);
    m_context->EnableDrawHiddenLine();

    m_context->SetPixelTolerance(2);

    auto drawer = m_context->DefaultDrawer();
    drawer->SetWireAspect(new Prs3d_LineAspect(Colors::Selection, Aspect_TOL_SOLID, 1.0));
    drawer->SetTypeOfHLR(Prs3d_TypeOfHLR::Prs3d_TOH_PolyAlgo);

    auto style = new Prs3d_Drawer();
    style->SetFaceBoundaryDraw(true);
    style->SetArrowAspect(new Prs3d_ArrowAspect(1.0, 35.0));
    style->SetFaceBoundaryAspect(new Prs3d_LineAspect(Quantity_NOC_BLACK, Aspect_TOL_SOLID, 1.0));
    m_context->SetHighlightStyle(style);

    applyWorkingContext();
}

// Working Plane Methods

gp_Quaternion Workspace::getWorkingPlaneRotation() const
{
    const gp_Pln& wp = m_WorkingPlane;
    gp_Mat mat(
        wp.XAxis().Direction().XYZ(),
        wp.YAxis().Direction().XYZ(),
        wp.Position().Direction().XYZ());
    return gp_Quaternion(mat);
}

void Workspace::setDefaultWorkingPlane(AIS_TypeOfPlane type)
{
    switch(type)
    {
    case AIS_TypeOfPlane::AIS_TOPL_XYPlane:
        m_WorkingPlane = gp_Pln(gp::XOY());
        break;
    case AIS_TypeOfPlane::AIS_TOPL_YZPlane:
        m_WorkingPlane = gp_Pln(gp::YOZ());
        break;
    case AIS_TypeOfPlane::AIS_TOPL_XZPlane:
        m_WorkingPlane = gp_Pln(gp::ZOX());
        break;
    default:
        m_WorkingPlane = gp_Pln(gp::XOY());
        break;
    }
    applyWorkingContext();
}

// Grid Computation Methods

gp_Pnt2d Workspace::computeGridPoint(const gp_Pnt2d& coord)
{
    gp_Pnt2d aCoord = coord;
    gp_Pnt2d gridPoint;

    // Apply inverse rotation if grid is rotated
    if(m_GridRotation != 0.0)
    {
        gp_Trsf2d trsf;
        trsf.SetRotation(gp_Pnt2d(0.0, 0.0), -m_GridRotation * M_PI / 180.0); // Degrees to radians
        aCoord.Transform(trsf);
    }

    if(m_GridType == GridTypes::Circular)
    {
        // Compute polar coordinates
        double angle = atan2(aCoord.Y(), aCoord.X());
        double circStep = 2 * M_PI / m_GridDivisions; // Full circle divided by divisions
        int iseg = static_cast<int>(std::round(angle / circStep));
        double radius = aCoord.Distance(gp_Pnt2d(0.0, 0.0));
        int icirc = static_cast<int>(std::round(radius / m_GridStep));

        // Compute grid point in polar form and convert to Cartesian
        double gridAngle = circStep * iseg;
        double gridRadius = m_GridStep * icirc;
        gridPoint = gp_Pnt2d(gridRadius * cos(gridAngle), gridRadius * sin(gridAngle));
    }
    else // Rectangular grid
    {
        int ix = static_cast<int>(std::round(aCoord.X() / m_GridStep));
        int iy = static_cast<int>(std::round(aCoord.Y() / m_GridStep));
        gridPoint = gp_Pnt2d(m_GridStep * ix, m_GridStep * iy);
    }

    // Apply forward rotation if grid is rotated
    if(m_GridRotation != 0.0)
    {
        gp_Trsf2d trsf;
        trsf.SetRotation(gp_Pnt2d(0.0, 0.0), m_GridRotation * M_PI / 180.0);
        gridPoint.Transform(trsf);
    }

    return gridPoint;
}

bool Workspace::projectToGrid(const std::shared_ptr<Viewport>& viewport, int screenX, int screenY, gp_Pnt& pnt)
{
    gp_Pln plane = m_WorkingPlane;
    if(!viewport->screenToPoint(plane, screenX, screenY, pnt))
    {
        return false;
    }

    double u, v;
    ElSLib::Parameters(plane, pnt, u, v);
    gp_Pnt2d uv(u, v);
    gp_Pnt2d gridUv = computeGridPoint(uv);
    pnt = ElSLib::Value(gridUv.X(), gridUv.Y(), plane);
    return true;
}

// Private Methods

void Workspace::applyWorkingContext()
{
    if(!m_context.IsNull() && !m_Viewer.IsNull())
    {
        m_Viewer->SetPrivilegedPlane(m_WorkingPlane.Position());
    }
    sig_PropertyChanged("WorkingPlane");
    sig_GridChanged(this);
}

// Setter Methods with Signal Emission

void Workspace::setGridEnabled(bool theValue)
{
    if(m_GridEnabled != theValue)
    {
        m_GridEnabled = theValue;
        sig_GridChanged(this);
        sig_PropertyChanged("GridEnabled");
    }
}

void Workspace::setGridType(GridTypes theValue)
{
    if(m_GridType != theValue)
    {
        m_GridType = theValue;
        sig_GridChanged(this);
        sig_PropertyChanged("GridType");
    }
}

void Workspace::setGridStep(double theValue)
{
    if(theValue > 0 && m_GridStep != theValue)
    {
        m_GridStep = theValue;
        sig_GridChanged(this);
        sig_PropertyChanged("GridStep");
    }
}

void Workspace::setGridRotation(double theValue)
{
    if(m_GridRotation != theValue)
    {
        m_GridRotation = theValue;
        sig_GridChanged(this);
        sig_PropertyChanged("GridRotation");
    }
}

void Workspace::setGridDivisions(int theValue)
{
    if(theValue > 0 && m_GridDivisions != theValue)
    {
        m_GridDivisions = theValue;
        sig_GridChanged(this);
        sig_PropertyChanged("GridDivisions");
    }
}

void Workspace::setWorkingPlane(const gp_Pln& theValue)
{
    m_WorkingPlane = theValue;
    applyWorkingContext();
}
