// Copyright [2024] SunCAD

#include "Core/Workspace.h"

#include <V3d_View.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <Aspect_Handle.hxx>
#include "Viewport.h"
//#include "Model.h"

//--------------------------------------------------------------------------------------------------
// Constructor and Destructor

Workspace::Workspace()
    : m_v3dViewer(nullptr),
    m_aisContext(nullptr),
    m_gridEnabled(false),
    m_needsRedraw(false),
    m_needsImmediateRedraw(false) {
}

Workspace::Workspace(Model* model) : Workspace() {
    m_model = model;
    m_viewports.append(new Viewport(this));
}

//Workspace::~Workspace() {
//    // Cleanup Viewports
//    for (auto viewport : m_viewports) {
//        delete viewport;
//    }
//    m_viewports.clear();
//}

//--------------------------------------------------------------------------------------------------
// Initialize V3d_Viewer and AIS_InteractiveContext

void Workspace::initV3dViewer() {
    // Initialize 3D viewer with graphic driver
    Handle(Aspect_DisplayConnection) aDisp = new Aspect_DisplayConnection();
    Handle(OpenGl_GraphicDriver) aDriver = new OpenGl_GraphicDriver(aDisp, false);
    // lets QOpenGLWidget to manage buffer swap
    aDriver->ChangeOptions().buffersNoSwap = true;
    // don't write into alpha channel
    aDriver->ChangeOptions().buffersOpaqueAlpha = true;
    // offscreen FBOs should be always used
    aDriver->ChangeOptions().useSystemBuffer = false;

    // create viewer
    m_v3dViewer = new V3d_Viewer(aDriver);
    m_v3dViewer->SetDefaultBackgroundColor(Quantity_NOC_BLACK);
    m_v3dViewer->SetDefaultLights();
    m_v3dViewer->SetLightOn();
    m_v3dViewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);

    // Create AIS context for interactive objects
    m_aisContext = new AIS_InteractiveContext(m_v3dViewer);
}

void Workspace::initAisContext() {
    if (m_v3dViewer.IsNull())
        initV3dViewer();

    if (m_aisContext.IsNull())
    {
        m_aisContext = new AIS_InteractiveContext(m_v3dViewer);
        m_aisContext->UpdateCurrentViewer();
    }

    m_aisContext->SetAutoActivateSelection(true);
    m_aisContext->SetToHilightSelected(false);
    m_aisContext->SetPickingStrategy(SelectMgr_PickingStrategy_OnlyTopmost);
    m_aisContext->SetDisplayMode((int)AIS_Shaded, false);
    m_v3dViewer->DisplayPrivilegedPlane(false, 1.0);
    m_aisContext->EnableDrawHiddenLine();

    // Reinit ais parameters
    _ApplyWorkingContext();
    m_aisContext->SetPixelTolerance(2);

    auto drawer = m_aisContext->DefaultDrawer();
    drawer->SetWireAspect(new Prs3d_LineAspect(ColorExtensions::toQuantityColor(Colors::Selection), Aspect_TOL_SOLID, 1.0));
    drawer->SetTypeOfHLR(Prs3d_TypeOfHLR::Prs3d_TOH_PolyAlgo);
}

void Workspace::_ApplyWorkingContext()
{
    if (!m_aisContext.IsNull())
    {
        // m_v3dViewer->SetPrivilegedPlane(_CurrentWorkingContext.WorkingPlane.Position);
    }
}

//--------------------------------------------------------------------------------------------------
// Getters

Handle(V3d_Viewer) Workspace::v3dViewer() const {
    return m_v3dViewer;
}

Handle(AIS_InteractiveContext) Workspace::aisContext() const {
    return m_aisContext;
}

bool Workspace::needsRedraw() const {
    return m_needsRedraw;
}

bool Workspace::needsImmediateRedraw() const {
    return m_needsImmediateRedraw;
}

//--------------------------------------------------------------------------------------------------
// Setters

void Workspace::setNeedsRedraw(bool value) {
    m_needsRedraw = value;
}

void Workspace::setNeedsImmediateRedraw(bool value) {
    m_needsImmediateRedraw = value;
}

//--------------------------------------------------------------------------------------------------
// Viewport handling
//
//std::vector<Viewport*>& Workspace::viewports() {
//    return m_viewports;
//}

//--------------------------------------------------------------------------------------------------
// Model handling

//const Model* Workspace::model() const {
//    return m_model;
//}
//
//void Workspace::setModel(Model* model) {
//    m_model = model;
//}
