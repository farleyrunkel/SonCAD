// Copyright [2024] SunCAD

#include "Core/Workspace.h"

#include <V3d_View.hxx>
#include <Graphic3d_GraphicDriver.hxx>
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
    initViewer();  // Initialize 3D viewer and context
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

void Workspace::initViewer() {
    // Initialize 3D viewer with graphic driver
    Handle(Graphic3d_GraphicDriver) graphicDriver;  // Graphic driver instance

    // Create 3D viewer and enable default lights
    m_v3dViewer = new V3d_Viewer(graphicDriver);
    m_v3dViewer->SetDefaultLights();
    m_v3dViewer->SetLightOn();

    // Create AIS context for interactive objects
    m_aisContext = new AIS_InteractiveContext(m_v3dViewer);
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
