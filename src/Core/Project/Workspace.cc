
#include "Core/Project/Workspace.h"

#include "Core/Project/WorkingContext.h"

Workspace::Workspace(const Handle(Document)& theDoc)
	: myDocument(theDoc)
	, myGlobalWorkingContext(new WorkingContext)
	, myNeedsRedraw(false)
	, myNeedsImmediateRedraw(false)
	, myGridEnabled(true)
	, myGridType(Rectangular)
	, myGridStep(10.0)
	, myGridRotation(0.0)
	, myGridDivisions(10)
{}

void Workspace::InitV3dViewer(const Handle(V3d_Viewer) & theViewer)
{
	if(myViewer.IsNull())
	{
		Handle(Aspect_DisplayConnection) aDisp = new Aspect_DisplayConnection();
		Handle(OpenGl_GraphicDriver) aDriver = new OpenGl_GraphicDriver(aDisp);
		aDriver->ChangeOptions().ffpEnable = false;
		aDriver->ChangeOptions().contextDebug = false;

		// create viewer
		myViewer = new V3d_Viewer(aDriver);
	}

	// Initialize 3D viewer with graphic driver

	myViewer->SetDefaultViewSize(1000.0);
	myViewer->SetDefaultViewProj(V3d_TypeOfOrientation::V3d_XposYposZpos);
	myViewer->SetDefaultBackgroundColor(Quantity_Color(NCollection_Vec3{0.3f, 0.3f, 0.3f}));
	myViewer->SetDefaultVisualization(V3d_TypeOfVisualization::V3d_ZBUFFER);
	myViewer->SetLightOn(new V3d_DirectionalLight(V3d_TypeOfOrientation::V3d_Zneg, Quantity_Color(Quantity_NOC_WHITE), true));
	myViewer->SetLightOn(new V3d_AmbientLight(Quantity_Color(Quantity_NOC_WHITE)));

	ApplyWorkingContext();
}

void Workspace::ApplyWorkingContext()
{
	if(!myContext.IsNull())
	{
		myViewer->SetPrivilegedPlane(myCurrentWorkingContext->GetWorkingPlane().Position());
	}
	emit_PropertyChanged("WorkingPlane");
	emit_GridChanged(this);
}
