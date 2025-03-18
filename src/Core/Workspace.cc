// Copyright [2024] SunCAD

#include "Core/Workspace.h"

#include <AIS_ViewCube.hxx>
#include <Aspect_Handle.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <V3d_View.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_TypeOfOrientation.hxx>
#include <V3d_TypeOfVisualization.hxx>
#include <Quantity_Color.hxx>
#include <V3d_DirectionalLight.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <AIS_Shape.hxx>

void Workspace::InitV3dViewer()
{
    Handle(Aspect_DisplayConnection) aDisp = new Aspect_DisplayConnection();
    Handle(OpenGl_GraphicDriver) aDriver = new OpenGl_GraphicDriver(aDisp, false);
    // lets QOpenGLWidget to manage buffer swap
    aDriver->ChangeOptions().buffersNoSwap = true;
    // don't Write into alpha channel
    aDriver->ChangeOptions().buffersOpaqueAlpha = true;
    // offscreen FBOs should be always used
    aDriver->ChangeOptions().useSystemBuffer = false;

    // create viewer
    _V3dViewer = new V3d_Viewer(aDriver);
    _V3dViewer->SetDefaultBackgroundColor(Quantity_NOC_BLACK);
    _V3dViewer->SetDefaultLights();
    _V3dViewer->SetLightOn();
    _V3dViewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);
}

void Workspace::InitAisContext()
{
    if(_V3dViewer.IsNull())
    {
        InitV3dViewer();
    }

    if(_AisContext.IsNull())
    {
        _AisContext = new AIS_InteractiveContext(_V3dViewer);
        _AisContext->UpdateCurrentViewer();
    }

    _AisContext->SetAutoActivateSelection(true);
    _AisContext->SetToHilightSelected(false);
    _AisContext->SetPickingStrategy(SelectMgr_PickingStrategy::SelectMgr_PickingStrategy_OnlyTopmost);
    _AisContext->SetDisplayMode(AIS_DisplayMode::AIS_Shaded, false);
    _V3dViewer->DisplayPrivilegedPlane(false, 1.0);
    _AisContext->EnableDrawHiddenLine();

    // Reinit ais parameters
    _ApplyWorkingContext();
    _AisContext->SetPixelTolerance(2);

    auto drawer = _AisContext->DefaultDrawer();
    //drawer->SetWireAspect(new Prs3d_LineAspect(ColorExtensions::toQuantityColor(Colors::Selection), Aspect_TOL_SOLID, 1.0));
    drawer->SetTypeOfHLR(Prs3d_TypeOfHLR::Prs3d_TOH_PolyAlgo);

    // try to set all AIS_InteractiveContext options for test 
    auto style = new Prs3d_Drawer();
    style->SetFaceBoundaryDraw(true);
    style->SetArrowAspect(new Prs3d_ArrowAspect(1.0, 35.0));
    style->SetFaceBoundaryAspect(new Prs3d_LineAspect(Quantity_NOC_BLACK, Aspect_TOL_SOLID, 1.0));
    _AisContext->SetHighlightStyle(style);
}

void Workspace::_ApplyWorkingContext() {}
