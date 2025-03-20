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

#include "Core/Workspace.h"

Viewport::Viewport(const Handle(Workspace)& workspace)
    : _Workspace(workspace), _RenderMode(SolidShaded), _Twist(0.0), _Scale(100.0)
{
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

// 更新渲染模式

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
