
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
	: myDocument(theDoc)
	, myNeedsRedraw(false)
	, myNeedsImmediateRedraw(false)
	, myGridEnabled(true)
	, myGridType(Rectangular)
	, myGridStep(10.0)
	, myGridRotation(0.0)
	, myGridDivisions(10)
{
	myGlobalWorkingContext = std::make_shared<WorkingContext>();
	myCurrentWorkingContext = myGlobalWorkingContext;

	myViewports.push_back(std::make_shared<Viewport>(shared_from_this()));
}

void Workspace::InitV3dViewer()
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

void Workspace::InitAisContext()
{
	if(myViewer.IsNull())
	{
		InitV3dViewer();
	}

	if(myContext.IsNull())
	{
		myContext = new AIS_InteractiveContext(myViewer);
		myContext->UpdateCurrentViewer();
	}

	myContext->SetAutoActivateSelection(true);
	myContext->SetToHilightSelected(false);
	myContext->SetPickingStrategy(SelectMgr_PickingStrategy::SelectMgr_PickingStrategy_OnlyTopmost);
	myContext->SetDisplayMode(AIS_DisplayMode::AIS_Shaded, false);
	myViewer->DisplayPrivilegedPlane(false, 1.0);
	myContext->EnableDrawHiddenLine();

	// Reinit ais parameters
	ApplyWorkingContext();
	myContext->SetPixelTolerance(2);

	auto drawer = myContext->DefaultDrawer();
	drawer->SetWireAspect(new Prs3d_LineAspect(Colors::Selection, Aspect_TOL_SOLID, 1.0));
	drawer->SetTypeOfHLR(Prs3d_TypeOfHLR::Prs3d_TOH_PolyAlgo);

	// try to set all AIS_InteractiveContext options for test 
	auto style = new Prs3d_Drawer();
	style->SetFaceBoundaryDraw(true);
	style->SetArrowAspect(new Prs3d_ArrowAspect(1.0, 35.0));
	style->SetFaceBoundaryAspect(new Prs3d_LineAspect(Quantity_NOC_BLACK, Aspect_TOL_SOLID, 1.0));
	myContext->SetHighlightStyle(style);

}


//! Working Plane

gp_Quaternion Workspace::GetWorkingPlaneRotation() const
{
	auto& wp = myWorkingPlane;
	gp_Mat mat(
		wp.XAxis().Direction().XYZ(),
		wp.YAxis().Direction().XYZ(),
		wp.Position().Direction().XYZ());
	return mat;
}

void Workspace::SetDefaultWorkingPlane(AIS_TypeOfPlane type)
{
	switch(type)
	{
	case AIS_TypeOfPlane::AIS_TOPL_XYPlane:
		myWorkingPlane = gp_Pln(gp::XOY());
		break;

	case AIS_TypeOfPlane::AIS_TOPL_YZPlane:
		myWorkingPlane = gp_Pln(gp::YOZ());
		break;

	case AIS_TypeOfPlane::AIS_TOPL_XZPlane:
		myWorkingPlane = gp_Pln(gp::ZOX());
		break;
	}
}

gp_Pnt2d Workspace::ComputeGridPoint(gp_Pnt2d coord)
{
	gp_Pnt2d gridPoint;

	// 如果有旋转，先反向旋转坐标
	if(myGridRotation != 0.0)
	{
		gp_Trsf2d trsf;
		trsf.SetRotation(gp_Pnt2d(0.0, 0.0), -myGridRotation * M_PI / 180.0); // 度转弧度
		coord.Transform(trsf);
	}

	// 根据网格类型计算网格点
	if(myGridType == GridTypes::Circular)
	{
		// 计算角度和圆周步长
		gp_Dir2d dx2d(1.0, 0.0); // X 轴方向
		double angle = dx2d.Angle(gp_Dir2d(coord.X(), coord.Y())); // 与 X 轴夹角
		double circStep = M_PI / myGridDivisions; // 圆周步长
		int iseg = static_cast<int>(std::round(angle / circStep)); // 角度段索引
		int icirc = static_cast<int>(std::round(coord.Distance(gp_Pnt2d(0.0, 0.0)) / myGridStep)); // 径向索引

		// 计算网格点：先在 X 轴上生成点，再旋转
		gridPoint = gp_Pnt2d(myGridStep * icirc, 0.0);
		gp_Trsf2d rot;
		rot.SetRotation(gp_Pnt2d(0.0, 0.0), circStep * iseg);
		gridPoint.Transform(rot);
	}
	else
	{ // GridTypes::Rectangular
		int ix = static_cast<int>(std::round(coord.X() / myGridStep)); // X 方向索引
		int iy = static_cast<int>(std::round(coord.Y() / myGridStep)); // Y 方向索引
		gridPoint = gp_Pnt2d(myGridStep * ix, myGridStep * iy);
	}

	// 如果有旋转，将结果正向旋转回去
	if(myGridRotation != 0.0)
	{
		gp_Trsf2d trsf;
		trsf.SetRotation(gp_Pnt2d(0.0, 0.0), myGridRotation * M_PI / 180.0); // 度转弧度
		gridPoint.Transform(trsf);
	}

	return gridPoint;
}

//! project to grid fro screen

bool Workspace::ProjectToGrid(const std::shared_ptr<Viewport>& viewport, int screenX, int screenY, gp_Pnt& pnt)
{
	gp_Pln plane = myWorkingPlane;
	if(!viewport->ScreenToPoint(plane, screenX, screenY, pnt))
	{
		return false;
	}
	double u = 0, v = 0;
	ElSLib::Parameters(plane, pnt, u, v);
	gp_Pnt2d uv(u, v);
	gp_Pnt2d gridUv = ComputeGridPoint(uv);

	pnt = ElSLib::Value(u, v, plane);

	return true;
}

void Workspace::ApplyWorkingContext()
{
	if(!myContext.IsNull())
	{
		myViewer->SetPrivilegedPlane(myCurrentWorkingContext->GetWorkingPlane().Position());
	}
	sig_PropertyChanged("WorkingPlane");
	sig_GridChanged(this);
}
