
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

	m_Viewports.push_back(std::make_shared<Viewport>(shared_from_this()));
}

void Workspace::initV3dViewer()
{
	if(m_Viewer.IsNull())
	{
		Handle(Aspect_DisplayConnection) aDisp = new Aspect_DisplayConnection();
		Handle(OpenGl_GraphicDriver) aDriver = new OpenGl_GraphicDriver(aDisp);
		aDriver->ChangeOptions().ffpEnable = false;
		aDriver->ChangeOptions().contextDebug = false;

		// create viewer
		m_Viewer = new V3d_Viewer(aDriver);
	}

	// Initialize 3D viewer with graphic driver

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

	if(m_Context.IsNull())
	{
		m_Context = new AIS_InteractiveContext(m_Viewer);
		m_Context->UpdateCurrentViewer();
	}

	m_Context->SetAutoActivateSelection(true);
	m_Context->SetToHilightSelected(false);
	m_Context->SetPickingStrategy(SelectMgr_PickingStrategy::SelectMgr_PickingStrategy_OnlyTopmost);
	m_Context->SetDisplayMode(AIS_DisplayMode::AIS_Shaded, false);
	m_Viewer->DisplayPrivilegedPlane(false, 1.0);
	m_Context->EnableDrawHiddenLine();

	// Reinit ais parameters
	applyWorkingContext();
	m_Context->SetPixelTolerance(2);

	auto drawer = m_Context->DefaultDrawer();
	drawer->SetWireAspect(new Prs3d_LineAspect(Colors::Selection, Aspect_TOL_SOLID, 1.0));
	drawer->SetTypeOfHLR(Prs3d_TypeOfHLR::Prs3d_TOH_PolyAlgo);

	// try to set all AIS_InteractiveContext options for test 
	auto style = new Prs3d_Drawer();
	style->SetFaceBoundaryDraw(true);
	style->SetArrowAspect(new Prs3d_ArrowAspect(1.0, 35.0));
	style->SetFaceBoundaryAspect(new Prs3d_LineAspect(Quantity_NOC_BLACK, Aspect_TOL_SOLID, 1.0));
	m_Context->SetHighlightStyle(style);

}


//! Working Plane

gp_Quaternion Workspace::getWorkingPlaneRotation() const
{
	auto& wp = m_WorkingPlane;
	gp_Mat mat(
		wp.XAxis().Direction().XYZ(),
		wp.YAxis().Direction().XYZ(),
		wp.Position().Direction().XYZ());
	return mat;
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
	}
}

gp_Pnt2d Workspace::computeGridPoint(const gp_Pnt2d& coord)
{
	gp_Pnt2d aCoord = coord;
	gp_Pnt2d gridPoint;

	// 如果有旋转，先反向旋转坐标
	if(m_GridRotation != 0.0)
	{
		gp_Trsf2d trsf;
		trsf.SetRotation(gp_Pnt2d(0.0, 0.0), -m_GridRotation * M_PI / 180.0); // 度转弧度
		aCoord.Transform(trsf);
	}

	// 根据网格类型计算网格点
	if(m_GridType == GridTypes::Circular)
	{
		// 计算角度和圆周步长
		gp_Dir2d dx2d(1.0, 0.0); // X 轴方向
		double angle = dx2d.Angle(gp_Dir2d(aCoord.X(), aCoord.Y())); // 与 X 轴夹角
		double circStep = M_PI / m_GridDivisions; // 圆周步长
		int iseg = static_cast<int>(std::round(angle / circStep)); // 角度段索引
		int icirc = static_cast<int>(std::round(aCoord.Distance(gp_Pnt2d(0.0, 0.0)) / m_GridStep)); // 径向索引

		// 计算网格点：先在 X 轴上生成点，再旋转
		gridPoint = gp_Pnt2d(m_GridStep * icirc, 0.0);
		gp_Trsf2d rot;
		rot.SetRotation(gp_Pnt2d(0.0, 0.0), circStep * iseg);
		gridPoint.Transform(rot);
	}
	else
	{ // GridTypes::Rectangular
		int ix = static_cast<int>(std::round(aCoord.X() / m_GridStep)); // X 方向索引
		int iy = static_cast<int>(std::round(aCoord.Y() / m_GridStep)); // Y 方向索引
		gridPoint = gp_Pnt2d(m_GridStep * ix, m_GridStep * iy);
	}

	// 如果有旋转，将结果正向旋转回去
	if(m_GridRotation != 0.0)
	{
		gp_Trsf2d trsf;
		trsf.SetRotation(gp_Pnt2d(0.0, 0.0), m_GridRotation * M_PI / 180.0); // 度转弧度
		gridPoint.Transform(trsf);
	}

	return gridPoint;
}

//! project to grid fro screen

bool Workspace::projectToGrid(const std::shared_ptr<Viewport>& viewport, int screenX, int screenY, gp_Pnt& pnt)
{
	gp_Pln plane = m_WorkingPlane;
	if(!viewport->screenToPoint(plane, screenX, screenY, pnt))
	{
		return false;
	}
	double u = 0, v = 0;
	ElSLib::Parameters(plane, pnt, u, v);
	gp_Pnt2d uv(u, v);
	gp_Pnt2d gridUv = computeGridPoint(uv);

	pnt = ElSLib::Value(u, v, plane);

	return true;
}

void Workspace::applyWorkingContext()
{
	if(!m_Context.IsNull())
	{
		m_Viewer->SetPrivilegedPlane(m_CurrentWorkingContext->GetWorkingPlane().Position());
	}
	sig_PropertyChanged("WorkingPlane");
	sig_GridChanged(this);
}
