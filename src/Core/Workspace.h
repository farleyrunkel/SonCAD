// Copyright [2024] SunCAD

#ifndef CORE_WORKSPACE_H
#define CORE_WORKSPACE_H

#include <QObject>

#include <AIS_InteractiveContext.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <gp_Pln.hxx>
#include <NCollection_Vector.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <Standard_Handle.hxx>
#include <V3d_Viewer.hxx>

#include "Comm/BaseObject.h"
#include "Core/Viewport.h"

class Model;

DEFINE_STANDARD_HANDLE(Workspace, BaseObject)

class Workspace final : public BaseObject
{
public:
    enum GridTypes
    {
        Rectangular,
        Circular
    };

public:
    Workspace(const Handle(Model)& model)
	{
        initViewer();

		_Document = model;

		Handle(Viewport) viewport = new Viewport(this);
        _Viewports.Append(viewport);
    }

    Workspace()
    {
        initViewer();
    }
    ~Workspace()
    {}

	NCollection_Vector<Handle(Viewport)>& GetViewports()
	{
		return _Viewports;
	}

    void initViewer()    
    {
        Handle(Aspect_DisplayConnection) aDisp = new Aspect_DisplayConnection();
        Handle(OpenGl_GraphicDriver) aDriver = new OpenGl_GraphicDriver(aDisp, false);
        // lets QOpenGLWidget to manage buffer swap
        aDriver->ChangeOptions().buffersNoSwap = true;
        // don't write into alpha channel
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

    Handle(V3d_Viewer) GetViewer()
    {
        return _V3dViewer;
    }

    Handle(V3d_Viewer) V3dViewer() const
    {
        return _V3dViewer;
    }

    const gp_Pln& WorkingPlane() const
    {
        return  gp_Pln();
    }

    bool GridEnabled() const
    {
        return _GridEnabled;
    }
    void SetGridEnabled(bool value)
    {}

    GridTypes GridType() const
    {
        return Circular;
    }

    void SetGridType(GridTypes)
    {
        return;
    }

    double GridStep() const
    {
        return 0;
    }
    void SetGridStep(double)
    {}

private:
	NCollection_Vector<Handle(Viewport)> _Viewports;

    Handle(Model) _Document;

    Handle(V3d_Viewer) _V3dViewer;
    Handle(AIS_InteractiveContext) _AisContext;
    bool _GridEnabled;
};

#endif  // CORE_WORKSPACE_H
