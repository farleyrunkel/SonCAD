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
    // 渲染模式枚举
    enum RenderModes
    {
        SolidShaded,
        HLR,
        Raytraced
    };

public:

    explicit Viewport(const Handle(Workspace)& workspace);

    Handle(Workspace) GetWorkspace()
    {
		return _Workspace;
    }

    // V3dView
	Handle(V3d_View) GetV3dView()
	{
		return _V3dView;
	}

    // 获取器和设置器
    gp_Pnt EyePoint()
    {
        if(_V3dView)
        {
            double xEye = 0, yEye = 0, zEye = 0;
            _V3dView->Eye(xEye, yEye, zEye);
            _EyePoint = gp_Pnt(xEye, yEye, zEye);
        }
        return _EyePoint;
    }

    void SetEyePoint(const gp_Pnt& point)
    {
        _EyePoint = point;
        if(_V3dView)
        {
            _V3dView->SetEye(_EyePoint.X(), _EyePoint.Y(), _EyePoint.Z());
            EyePointChanged(_EyePoint);  // 传递参数
        }
    }

    gp_Pnt TargetPoint()
    {
        if(_V3dView)
        {
            double xAt = 0, yAt = 0, zAt = 0;
            _V3dView->At(xAt, yAt, zAt);
            _TargetPoint = gp_Pnt(xAt, yAt, zAt);
        }
        return _TargetPoint;
    }

    void SetTargetPoint(const gp_Pnt& point)
    {
        _TargetPoint = point;
        if(_V3dView)
        {
            _V3dView->SetAt(_TargetPoint.X(), _TargetPoint.Y(), _TargetPoint.Z());
            TargetPointChanged(_TargetPoint);  // 传递参数
        }
    }

    double Twist()
    {
        if(_V3dView)
        {
            _Twist = _V3dView->Twist() * 180.0 / M_PI;  // 转换为度
        }
        return _Twist;
    }

    void SetTwist(double value)
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

    double Scale()
    {
        if(_V3dView)
        {
            _Scale = _V3dView->Scale();
        }
        return _Scale;
    }

    void SetScale(double value)
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

    RenderModes RenderMode() const
    {
        return _RenderMode;
    }

    void setRenderMode(RenderModes mode)
    {
        if(_RenderMode != mode)
        {
            _RenderMode = mode;
            UpdateRenderMode();
            RenderModeChanged(_RenderMode);  // 传递参数
        }
    }

    // 初始化 Viewport，支持 MSAA
    void Init(bool useMsaa);

    // 更新渲染模式
    void UpdateRenderMode();

    // 析构函数
    ~Viewport()
    {
        if(_V3dView)
        {
            _V3dView->Remove();
        }
    }

    void OnViewMoved()
    {
        _RaiseViewportChanged();
    }

    void _ValidateViewGeometry()
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

	gp_Pln GetViewPlane()
	{
		auto eyeDir = GetViewDirection();
		return gp_Pln(_TargetPoint, eyeDir);
	}

	gp_Lin GetViewLine()
	{
		return gp_Lin(_EyePoint, GetViewDirection());
	}

    gp_Dir GetViewDirection()
    {
		_ValidateViewGeometry();

        gp_Vec eyeVector(_EyePoint, _TargetPoint);
        return gp_Dir(eyeVector);
    }

    gp_Ax1 ViewAxis(int screenX, int screenY)
    {
		if(_V3dView.IsNull())
		{
			return gp::OX();
		}

		double px = 0, py = 0, pz = 0;
        _V3dView->Convert(screenX, screenY, px, py, pz);

		return gp_Ax1(gp_Pnt(px, py, pz), GetViewDirection());
    }

    gp_Dir GetUpDirection()
    {
        if(_V3dView.IsNull())
        {
            return gp_Dir(0, 0, 1);
        }

        double xUp = 0, yUp = 0, zUp = 0;
        _V3dView->Up(xUp, yUp, zUp);
        return gp_Dir(xUp, yUp, zUp);
    }

    gp_Dir GetRightDirection()
    {
		auto upDir = GetUpDirection();
        auto eyeDir = GetViewDirection();

		return upDir.Crossed(eyeDir);
    }

	double DpiScale() const
	{
		return _DpiScale;
	}

	Handle(AIS_AnimationCamera) AisAnimationCamera() const
	{
		return _AisAnimationCamera;
	}

public:
    boost::signals2::signal<void(const gp_Pnt&)> EyePointChanged;
    boost::signals2::signal<void(const gp_Pnt&)> TargetPointChanged;
    boost::signals2::signal<void(double)> TwistChanged;
    boost::signals2::signal<void(double)> ScaleChanged;
    boost::signals2::signal<void(RenderModes)> RenderModeChanged;

    boost::signals2::signal<void(const Handle(Viewport)&)> ViewportChanged;

private:
    void _RaiseViewportChanged()
    {
        ViewportChanged(this);
    }

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
