#ifndef myViewport_h_
#define myViewport_h_

#include <boost/signals2.hpp>

#include <AIS_InteractiveContext.hxx>
#include <gp_Pnt.hxx>
 
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_AnimationCamera.hxx>
#include <Graphic3d_Vec2.hxx>
#include <Quantity_Color.hxx>

#include "Core/Project/Document.h"
#include "Comm/BaseObject.h"

class Workspace;

class Viewport : public enable_property_changed_signal
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
	explicit Viewport(const std::shared_ptr<Workspace>& workspace);

	double PixelSize() const
	{
		if(!myV3dView.IsNull() && myV3dView->IfWindow())
		{
			return myV3dView->Convert(1.0);
		}
		return 1.0;
	}

	Graphic3d_Vec2d Size() const
	{
		double width = 0, height = 0;
		myV3dView->Size(width, height);
		return Graphic3d_Vec2d(width, height);
	}

	Graphic3d_Vec2i ScreenSize() const
	{
		double pixelSize = PixelSize();
		double width = 100, height = 100;
		myV3dView->Size(width, height);
		return Graphic3d_Vec2i(width / pixelSize, height / pixelSize);
	}

	double GizmoScale() const
	{
		double width = 100, height = 100;
		myV3dView->Size(width, height);
		double scale = Min(width, height) / 10.0;
		return scale;
	}

	double DpiScale() const
	{
		return myDpiScale;
	}

	void SetDpiScale(double dpiScale)
	{
		myDpiScale = dpiScale;
	}

	void Init(bool useMsaa);

	bool ScreenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt);

	void UpdateRenderMode();

	void Resize();

private:
	std::shared_ptr<Workspace> myWorkspace;
	std::shared_ptr<Document> myDocument;

	Handle(V3d_Viewer) myViewer;
	Handle(V3d_View) myV3dView;
	Handle(AIS_InteractiveContext) myContext;
	Handle(AIS_AnimationCamera) myAnimationCamera;

	RenderModes myRenderMode = RenderModes::SolidShaded;

	gp_Pnt myEyePoint = gp_Pnt(10, 10, 10);
	gp_Pnt myTargetPoint = gp_Pnt(0, 0, 0);

	double myTwist = 0.0f;
	double myScale = 100.0f;
	double myDpiScale = 1.0;

	bool myNeedsRedraw;
	bool myNeedsImmediateRedraw;

private:
	ViewportChangedSignal emit_ViewportChanged;
};

#endif // !_Viewport_h_
