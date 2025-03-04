
#include "Core/Project/Viewport.h"

#include <AIS_AnimationCamera.hxx>
#include <Graphic3d_RenderingMode.hxx>
#include <Graphic3d_RenderingParams.hxx>
#include <Graphic3d_RenderTransparentMethod.hxx>
#include <Quantity_Color.hxx>

#include "Core/Project/Workspace.h"

Viewport::Viewport(const std::shared_ptr<Workspace>& workspace)
    : myWorkspace(workspace)
{}

void Viewport::Init(bool useMsaa)
{
	if(!myV3dView.IsNull())
	{
		return;
	}

	myV3dView = myWorkspace->GetViewer()->CreateView();

	myAnimationCamera = new AIS_AnimationCamera("ViewCamera", myV3dView);

	myV3dView->SetBgGradientColors(
		Quantity_Color(0.624f, 0.714f, 0.804f, Quantity_TOC_RGB),
		Quantity_Color(0.424f, 0.482f, 0.545f, Quantity_TOC_RGB),
		Aspect_GFM_VER,
		false
	);

	auto renderParams = myV3dView->ChangeRenderingParams();

	renderParams.NbMsaaSamples = useMsaa ? 4 : 0;
	renderParams.IsAntialiasingEnabled = useMsaa;
	renderParams.TransparencyMethod = Graphic3d_RTM_BLEND_OIT;
	renderParams.Method = Graphic3d_RM_RASTERIZATION;
	renderParams.RaytracingDepth = 3;
	renderParams.IsShadowEnabled = true;
	renderParams.IsReflectionEnabled = true;
	renderParams.IsTransparentShadowEnabled = true;

	myV3dView->SetAt(myTargetPoint.X(), myTargetPoint.Y(), myTargetPoint.Z());
	myV3dView->SetEye(myEyePoint.X(), myEyePoint.Y(), myEyePoint.Z());
	myV3dView->SetScale(myScale);
	myV3dView->SetTwist(myTwist);
}

bool Viewport::ScreenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt)
{
    return false;
}


void Viewport::UpdateRenderMode()
{
	if(myV3dView.IsNull())
	{
		return;
	}

	myV3dView->SetComputedMode(myRenderMode == RenderModes::HLR);

	auto renderParams = myV3dView->ChangeRenderingParams();

	if(myRenderMode == RenderModes::Raytraced)
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
	if(myV3dView.IsNull())
	{
		return;
	}
	myV3dView->MustBeResized();

	emit_ViewportChanged(this);
}
