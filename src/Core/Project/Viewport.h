#ifndef myViewport_h_
#define myViewport_h_

#include <boost/signals2.hpp>

#include <AIS_InteractiveContext.hxx>
#include <gp_Pnt.hxx>
#include <Standard_Transient.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_AnimationCamera.hxx>

#include "Core/Project/Document.h"

class Workspace;

DEFINE_STANDARD_HANDLE(Viewport, Standard_Transient)

class Viewport final : public Standard_Transient
{
	using ViewportChangedSignal = boost::signals2::signal<void(Viewport*)>;
public:
	enum RenderModes
	{
		SolidShaded,
		HLR,
		Raytraced
	};

public:
	explicit Viewport(const Handle(Workspace)& workspace);

    bool ScreenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt);

private:
	Handle(Workspace) myWorkspace;
	Handle(Document) myDocument;

	Handle(V3d_Viewer) myViewer;
	Handle(V3d_View) myV3dView;
	Handle(AIS_InteractiveContext) myContext;
	Handle(AIS_AnimationCamera) myAnimationCamera;

	gp_Pnt myEyePoint = gp_Pnt(10, 10, 10);
	gp_Pnt myTargetPoint = gp_Pnt(0, 0, 0);
	double myTwist = 0.0f;
	double myScale = 100.0f;
	RenderModes myRenderMode = RenderModes::SolidShaded;
	double myDpiScale = 1.0;

	bool myNeedsRedraw;
	bool myNeedsImmediateRedraw;

private:
	ViewportChangedSignal emit_ViewportChanged;
};

#endif // !_Viewport_h_
