// Copyright [2024] SunCAD

#ifndef CORE_VIEWPORT_H
#define CORE_VIEWPORT_H

#include <cmath>

#include <boost/signals2.hpp>

#include <QObject>
#include <QSharedPointer>

#include <AIS_AnimationCamera.hxx>
#include <Aspect_GradientFillMethod.hxx>
#include <gp.hxx>
#include <gp_Ax1.hxx>
#include <gp_Dir.hxx>
#include <gp_Lin.hxx>
#include <gp_Pnt.hxx>
#include <Graphic3d_RenderingMode.hxx>
#include <Graphic3d_RenderingParams.hxx>
#include <Graphic3d_RenderTransparentMethod.hxx>
#include <V3d_View.hxx>

#include "Comm/BaseObject.h"

class Workspace;

DEFINE_STANDARD_HANDLE(Viewport, BaseObject)

class Viewport : public BaseObject
{
public:
    // äÖÈ¾Ä£Ê½Ã¶¾Ù
    enum RenderModes
    {
        SolidShaded,
        HLR,
        Raytraced
    };

public:
    explicit Viewport(const Handle(Workspace)& workspace);
    ~Viewport();

public:
    Handle(Workspace) GetWorkspace();

	Handle(V3d_View) V3dView();

    gp_Pnt EyePoint();

    void SetEyePoint(const gp_Pnt& point);

    gp_Pnt TargetPoint();

    void SetTargetPoint(const gp_Pnt& point);

    double Twist();

    void SetTwist(double value);

    double Scale();

    void SetScale(double value);

    RenderModes RenderMode() const;

    void setRenderMode(RenderModes mode);

    void Init(bool useMsaa);

    void UpdateRenderMode();

    void Resize();

    void OnViewMoved();

	gp_Pln GetViewPlane();
	gp_Lin GetViewLine();
    gp_Dir GetViewDirection();
    gp_Ax1 ViewAxis(int screenX, int screenY);
    gp_Dir GetUpDirection();
    gp_Dir GetRightDirection();

	double DpiScale() const;

	Handle(AIS_AnimationCamera) AisAnimationCamera() const;

    bool ScreenToPoint(int screenX, int screenY, gp_Pnt& point);

	bool ScreenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& point);
    bool PointToScreen(const gp_Pnt& point, int& screenX, int& screenY);

public:
    boost::signals2::signal<void(const gp_Pnt&)> EyePointChanged;
    boost::signals2::signal<void(const gp_Pnt&)> TargetPointChanged;
    boost::signals2::signal<void(double)> TwistChanged;
    boost::signals2::signal<void(double)> ScaleChanged;
    boost::signals2::signal<void(RenderModes)> RenderModeChanged;
    boost::signals2::signal<void(const Handle(Viewport)&)> ViewportChanged;

private:
    void _RaiseViewportChanged();

    void _ValidateViewGeometry();

private:
    Handle(Workspace) _Workspace;
    gp_Pnt _EyePoint = gp_Pnt(10, 10, 10);
    gp_Pnt _TargetPoint = gp_Pnt(0, 0, 0);
    double _Twist = 0.0;
    double _Scale = 100.0;

    RenderModes _RenderMode;

    double _DpiScale = 1.0;

    Handle(V3d_View) _V3dView;
    Handle(AIS_AnimationCamera) _AisAnimationCamera;
};

#endif  // CORE_VIEWPORT_H
