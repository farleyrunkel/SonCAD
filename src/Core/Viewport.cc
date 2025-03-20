// Copyright [2024] SunCAD

#include "Core/Viewport.h"

#include <IntAna_IntConicQuad.hxx>
#include <Precision.hxx>
#include <gp_Lin.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <Graphic3d_RenderingParams.hxx>
#include <Quantity_Color.hxx>
#include <AIS_AnimationCamera.hxx>
#include <ProjLib.hxx>
#include <ElSLib.hxx>

#include "Core/Workspace.h"

Viewport::Viewport(const Handle(Workspace)& workspace)
    : _Workspace(workspace), _RenderMode(SolidShaded), _Twist(0.0), _Scale(100.0)
{
}

Handle(Workspace) Viewport::GetWorkspace()
{
    return _Workspace;
}

// V3dView

Handle(V3d_View) Viewport::V3dView()
{
    return _V3dView;
}

// 获取器和设置器

gp_Pnt Viewport::EyePoint()
{
    if(_V3dView)
    {
        double xEye = 0, yEye = 0, zEye = 0;
        _V3dView->Eye(xEye, yEye, zEye);
        _EyePoint = gp_Pnt(xEye, yEye, zEye);
    }
    return _EyePoint;
}

void Viewport::SetEyePoint(const gp_Pnt& point)
{
    _EyePoint = point;
    if(_V3dView)
    {
        _V3dView->SetEye(_EyePoint.X(), _EyePoint.Y(), _EyePoint.Z());
        EyePointChanged(_EyePoint);  // 传递参数
    }
}

gp_Pnt Viewport::TargetPoint()
{
    if(_V3dView)
    {
        double xAt = 0, yAt = 0, zAt = 0;
        _V3dView->At(xAt, yAt, zAt);
        _TargetPoint = gp_Pnt(xAt, yAt, zAt);
    }
    return _TargetPoint;
}

void Viewport::SetTargetPoint(const gp_Pnt& point)
{
    _TargetPoint = point;
    if(_V3dView)
    {
        _V3dView->SetAt(_TargetPoint.X(), _TargetPoint.Y(), _TargetPoint.Z());
        TargetPointChanged(_TargetPoint);  // 传递参数
    }
}

double Viewport::Twist()
{
    if(_V3dView)
    {
        _Twist = _V3dView->Twist() * 180.0 / M_PI;  // 转换为度
    }
    return _Twist;
}

void Viewport::SetTwist(double value)
{
    if(_V3dView)
    {
        _V3dView->SetTwist(value * M_PI / 180.0);  // 转换为弧度
        if(_Twist != value)
        {
            _Twist = value;
            TwistChanged(_Twist);  // 传递参数
        }
    }
}

double Viewport::Scale()
{
    if(_V3dView)
    {
        _Scale = _V3dView->Scale();
    }
    return _Scale;
}

void Viewport::SetScale(double value)
{
    if(_V3dView)
    {
        _V3dView->SetScale(value);
        if(_Scale != value)
        {
            _Scale = value;
            ScaleChanged(_Scale);  // 传递参数
        }
    }
}

Viewport::RenderModes Viewport::RenderMode() const
{
    return _RenderMode;
}

void Viewport::setRenderMode(RenderModes mode)
{
    if(_RenderMode != mode)
    {
        _RenderMode = mode;
        UpdateRenderMode();
        RenderModeChanged(_RenderMode);  // 传递参数
    }
}

void Viewport::Init(bool useMsaa)
{
    if(!_V3dView.IsNull())
    {
        return;
    }

    _V3dView = _Workspace->V3dViewer()->CreateView();
    _AisAnimationCamera = new AIS_AnimationCamera("ViewCamera", _V3dView);

    _V3dView->SetBgGradientColors(Quantity_Color(0.624, 0.714, 0.804, Quantity_TOC_sRGB),
                                  Quantity_Color(0.424, 0.482, 0.545, Quantity_TOC_sRGB),
                                  Aspect_GFM_VER, false);

    Graphic3d_RenderingParams& renderParams = _V3dView->ChangeRenderingParams();
    renderParams.NbMsaaSamples = useMsaa ? 4 : 0;
    renderParams.IsAntialiasingEnabled = useMsaa;
    renderParams.TransparencyMethod = Graphic3d_RTM_DEPTH_PEELING_OIT;
    renderParams.Method = Graphic3d_RM_RASTERIZATION;
    renderParams.RaytracingDepth = 3;
    renderParams.IsShadowEnabled = true;
    renderParams.IsReflectionEnabled = true;
    renderParams.IsTransparentShadowEnabled = true;

    // 重新初始化视图参数
    SetTargetPoint(_TargetPoint);
    SetEyePoint(_EyePoint);
    SetScale(_Scale);
    SetTwist(_Twist);
    UpdateRenderMode();
}

Viewport::~Viewport()
{
    if(_V3dView)
    {
        _V3dView->Remove();
    }
}

void Viewport::OnViewMoved()
{
    _RaiseViewportChanged();
}

gp_Pln Viewport::GetViewPlane()
{
    auto eyeDir = GetViewDirection();
    return gp_Pln(_TargetPoint, eyeDir);
}

gp_Lin Viewport::GetViewLine()
{
    return gp_Lin(_EyePoint, GetViewDirection());
}

gp_Dir Viewport::GetViewDirection()
{
    _ValidateViewGeometry();

    gp_Vec eyeVector(_EyePoint, _TargetPoint);
    return gp_Dir(eyeVector);
}

gp_Ax1 Viewport::ViewAxis(int screenX, int screenY)
{
    if(_V3dView.IsNull())
    {
        return gp::OX();
    }

    double px = 0, py = 0, pz = 0;
    _V3dView->Convert(screenX, screenY, px, py, pz);

    return gp_Ax1(gp_Pnt(px, py, pz), GetViewDirection());
}

gp_Dir Viewport::GetUpDirection()
{
    if(_V3dView.IsNull())
    {
        return gp_Dir(0, 0, 1);
    }

    double xUp = 0, yUp = 0, zUp = 0;
    _V3dView->Up(xUp, yUp, zUp);
    return gp_Dir(xUp, yUp, zUp);
}

gp_Dir Viewport::GetRightDirection()
{
    auto upDir = GetUpDirection();
    auto eyeDir = GetViewDirection();

    return upDir.Crossed(eyeDir);
}

double Viewport::DpiScale() const
{
    return _DpiScale;
}

Handle(AIS_AnimationCamera) Viewport::AisAnimationCamera() const
{
    return _AisAnimationCamera;
}

bool Viewport::ScreenToPoint(int screenX, int screenY, gp_Pnt& resultPnt)
{
    if(_V3dView.IsNull())
    {
        return false;
    }

    try
    {
        auto viewPlane = GetViewPlane();
        double x = 0, y = 0, z = 0;
        _V3dView->Convert(screenX, screenY, x, y, z);
        gp_Pnt convertedPoint(x, y, z);
        gp_Pnt2d convertedPointOnPlane = ProjLib::Project(viewPlane, convertedPoint);

        resultPnt = ElSLib::Value(convertedPointOnPlane.X(), convertedPointOnPlane.Y(), viewPlane);
        return true;
    }
    catch(std::exception& e)
	{
        std::cerr << "Viewport::ScreenToPoint: " << e.what() << std::endl;
    }
	resultPnt = gp_Pnt(0, 0, 0);
    return false;
}

bool Viewport::ScreenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt)
{
    if(_V3dView.IsNull())
    {
        return false;
    }
    try
    {
        _ValidateViewGeometry();

        if(_V3dView->IfWindow())
        {
            double xv = 0, yv = 0, zv = 0;
            double vx = 0, vy = 0, vz = 0;

            _V3dView->Convert(screenX, screenY, xv, yv, zv);
            _V3dView->Proj(vx, vy, vz);

            gp_Lin line(gp_Pnt(xv, yv, zv), gp_Dir(vx, vy, vz));
            IntAna_IntConicQuad intersection(line, plane, Precision::Confusion());

            if(intersection.IsDone()
			   && !intersection.IsParallel()
			   && intersection.NbPoints() > 0)
			{
                resultPnt = intersection.Point(1);
				return true;
			}
        }
    }
	catch(std::exception& e)
	{
		std::cerr << "Viewport::ScreenToPoint: " << e.what() << std::endl;
	}

	resultPnt = gp_Pnt(0, 0, 0);
    return true;
}

bool Viewport::PointToScreen(const gp_Pnt& point, int& screenX, int& screenY)
{
	if(_V3dView.IsNull())
	{
		return false;
	}

	try
	{
        int x = 0, y = 0;
        _V3dView->Convert(point.X(), point.Y(), point.Z(), x, y);

        screenX = x;
        screenY = y;
	}
    catch(std::exception& e)
    {
        std::cerr << "Viewport::PointToScreen: " << e.what() << std::endl;
    }
    screenX = 0;
    screenY = 0;
    return false;
}

void Viewport::_ValidateViewGeometry()
{
    if(_V3dView.IsNull())
    {
        return;
    }

    // If distance is 0, the parameters cannot be restored
    if(_V3dView->Camera()->Distance() == 0.0)
    {
        _V3dView->Camera()->SetDistance(0.00001);
    }
}

void Viewport::_RaiseViewportChanged()
{
    ViewportChanged(this);
}

void Viewport::UpdateRenderMode()
{
    if(!_V3dView) return;

    _V3dView->SetComputedMode(_RenderMode == HLR);

    auto& renderParams = _V3dView->ChangeRenderingParams();
    if(_RenderMode == Raytraced)
    {
        renderParams.Method = Graphic3d_RM_RAYTRACING;
    }
    else
    {
        renderParams.Method = Graphic3d_RM_RASTERIZATION;
    }
}
void Viewport::Resize()
{
    _V3dView->MustBeResized();
    RaisePropertyChanged("PixelSize");
    RaisePropertyChanged("GizmoScale");
    _RaiseViewportChanged();
}
