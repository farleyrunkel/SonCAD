#ifndef m_Viewport_h_
#define m_Viewport_h_

#include <boost/signals2.hpp>

#include <AIS_InteractiveContext.hxx>
#include <gp_Pnt.hxx>
 
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_AnimationCamera.hxx>
#include <Graphic3d_Vec2.hxx>
#include <Quantity_Color.hxx>

#include "Core/Project/Document.h"
#include "Comm/PropertySignal.h"

class Workspace;

class Viewport : public enable_property_changed_signal
{
public:
	enum RenderModes
	{
		SolidShaded,
		HLR,
		Raytraced
	};

public:
	Viewport(){}
	explicit Viewport(const std::shared_ptr<Workspace>& workspace);

	auto view() const 
	{
		return m_V3dView;
	}

	double pixelSize() const
	{
		if(!m_V3dView.IsNull() && m_V3dView->IfWindow())
		{
			return m_V3dView->Convert(1.0);
		}
		return 1.0;
	}

	Graphic3d_Vec2d size() const
	{
		double width = 0, height = 0;
		m_V3dView->Size(width, height);
		return Graphic3d_Vec2d(width, height);
	}

	Graphic3d_Vec2i screenSize() const
	{
		double pixel = pixelSize();
		double width = 100, height = 100;
		m_V3dView->Size(width, height);
		return Graphic3d_Vec2i(width / pixel, height / pixel);
	}

	double gizmoScale() const
	{
		double width = 100, height = 100;
		m_V3dView->Size(width, height);
		double scale = Min(width, height) / 10.0;
		return scale;
	}

	double dpiScale() const
	{
		return m_DpiScale;
	}

	void setDpiScale(double dpiScale)
	{
		m_DpiScale = dpiScale;
	}

	void init(bool useMsaa);

	bool screenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt);

	void updateRenderMode();

	auto v3dView() const
	{
		return m_V3dView;
	}

	auto workspace() const
	{
		return m_Workspace;
	}

	void resize();

public:
	boost::signals2::signal<void(Viewport*)> sig_ViewportChanged;

private:
	std::shared_ptr<Workspace> m_Workspace;
	std::shared_ptr<Document> m_Document;

	Handle(V3d_Viewer) m_Viewer;
	Handle(V3d_View) m_V3dView;
	Handle(AIS_InteractiveContext) m_Context;
	Handle(AIS_AnimationCamera) m_AnimationCamera;

	RenderModes m_RenderMode = RenderModes::SolidShaded;

	gp_Pnt m_EyePoint = gp_Pnt(10, 10, 10);
	gp_Pnt m_TargetPoint = gp_Pnt(0, 0, 0);

	double m_Twist = 0.0f;
	double m_Scale = 100.0f;
	double m_DpiScale = 1.0;

	bool m_NeedsRedraw;
	bool m_NeedsImmediateRedraw;
};

#endif // !_Viewport_h_
