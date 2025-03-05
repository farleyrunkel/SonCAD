
#include "Core/Project/Viewport.h"

#include <AIS_AnimationCamera.hxx>
#include <Graphic3d_RenderingMode.hxx>
#include <Graphic3d_RenderingParams.hxx>
#include <Graphic3d_RenderTransparentMethod.hxx>
#include <Quantity_Color.hxx>

#include "Core/Project/Workspace.h"

Viewport::Viewport(const std::shared_ptr<Workspace>& workspace)
    : m_Workspace(workspace)
{}

void Viewport::init(bool useMsaa)
{
	if(!m_V3dView.IsNull())
	{
		return;
	}

	m_V3dView = m_Workspace->getViewer()->CreateView();

	m_AnimationCamera = new AIS_AnimationCamera("ViewCamera", m_V3dView);

	m_V3dView->SetBgGradientColors(
		Quantity_Color(0.624f, 0.714f, 0.804f, Quantity_TOC_RGB),
		Quantity_Color(0.424f, 0.482f, 0.545f, Quantity_TOC_RGB),
		Aspect_GFM_VER,
		false
	);

	auto renderParams = m_V3dView->ChangeRenderingParams();

	renderParams.NbMsaaSamples = useMsaa ? 4 : 0;
	renderParams.IsAntialiasingEnabled = useMsaa;
	renderParams.TransparencyMethod = Graphic3d_RTM_BLEND_OIT;
	renderParams.Method = Graphic3d_RM_RASTERIZATION;
	renderParams.RaytracingDepth = 3;
	renderParams.IsShadowEnabled = true;
	renderParams.IsReflectionEnabled = true;
	renderParams.IsTransparentShadowEnabled = true;

	m_V3dView->SetAt(m_TargetPoint.X(), m_TargetPoint.Y(), m_TargetPoint.Z());
	m_V3dView->SetEye(m_EyePoint.X(), m_EyePoint.Y(), m_EyePoint.Z());
	m_V3dView->SetScale(m_Scale);
	m_V3dView->SetTwist(m_Twist);
}

bool Viewport::screenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt)
{
    return false;
}


void Viewport::updateRenderMode()
{
	if(m_V3dView.IsNull())
	{
		return;
	}

	m_V3dView->SetComputedMode(m_RenderMode == RenderModes::HLR);

	auto renderParams = m_V3dView->ChangeRenderingParams();

	if(m_RenderMode == RenderModes::Raytraced)
	{
		renderParams.Method = Graphic3d_RM_RAYTRACING;
	}
	else
	{
		renderParams.Method = Graphic3d_RM_RASTERIZATION;
	}
}

void Viewport::resize()
{
	if(m_V3dView.IsNull())
	{
		return;
	}
	m_V3dView->MustBeResized();

	sig_ViewportChanged(this);
}
