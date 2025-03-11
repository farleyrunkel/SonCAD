#include "Core/Project/Viewport.h"

#include <stdexcept>

#include <AIS_AnimationCamera.hxx>
#include <Graphic3d_RenderingMode.hxx>
#include <Graphic3d_RenderingParams.hxx>
#include <Graphic3d_RenderTransparentMethod.hxx>
#include <Quantity_Color.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>

#include "Core/Project/Workspace.h"

boost::signals2::signal<void(Viewport*)> Viewport::sig_ViewportChanged;

Viewport::Viewport(const std::shared_ptr<Workspace>& workspace)
    : m_Workspace(workspace)
{}

Viewport::~Viewport()
{
    if(!m_AnimationCamera.IsNull())
    {
        m_AnimationCamera->Delete();
    }
    if(!m_V3dView.IsNull())
    {
        m_V3dView->Remove();
    }
}

void Viewport::init(bool useMsaa)
{
    if(!m_V3dView.IsNull() || !m_Workspace)
    {
        return;
    }

    m_Viewer = m_Workspace->getViewer();
    m_V3dView = m_Viewer->CreateView();
    m_Context = m_Workspace->aisContext(); // 假设 Workspace 提供此方法
    m_AnimationCamera = new AIS_AnimationCamera("ViewCamera", m_V3dView);

    m_V3dView->SetBgGradientColors(
        Quantity_Color(0.624f, 0.714f, 0.804f, Quantity_TOC_RGB),
        Quantity_Color(0.424f, 0.482f, 0.545f, Quantity_TOC_RGB),
        Aspect_GFM_VER,
        false
    );

    auto& renderParams = m_V3dView->ChangeRenderingParams();
    renderParams.NbMsaaSamples = useMsaa ? 4 : 0;
    renderParams.IsAntialiasingEnabled = useMsaa;
    renderParams.TransparencyMethod = Graphic3d_RTM_BLEND_OIT;
    renderParams.Method = Graphic3d_RM_RASTERIZATION;
    renderParams.RaytracingDepth = 3;
    renderParams.IsShadowEnabled = true;
    renderParams.IsReflectionEnabled = true;
    renderParams.IsTransparentShadowEnabled = true;

    // 初始化相机参数
    setTargetPoint(m_TargetPoint);
    setEyePoint(m_EyePoint);
    setScale(m_Scale);
    setTwist(m_Twist);
    updateRenderMode();

    sig_ViewportChanged(this);
}

double Viewport::pixelSize() const
{
    if(!m_V3dView.IsNull() && m_V3dView->IfWindow())
    {
        return m_V3dView->Convert(1.0);
    }
    return 1.0;
}

Graphic3d_Vec2d Viewport::size() const
{
    if(!m_V3dView.IsNull())
    {
        double width = 0, height = 0;
        m_V3dView->Size(width, height);
        return Graphic3d_Vec2d(width, height);
    }
    return Graphic3d_Vec2d(100.0, 100.0);
}

Graphic3d_Vec2i Viewport::screenSize() const
{
    if(!m_V3dView.IsNull())
    {
        double pixel = pixelSize();
        double width = 0, height = 0;
        m_V3dView->Size(width, height);
        return Graphic3d_Vec2i(static_cast<int>(width / pixel), static_cast<int>(height / pixel));
    }
    return Graphic3d_Vec2i(100, 100);
}

double Viewport::gizmoScale() const
{
    if(!m_V3dView.IsNull())
    {
        double width = 0, height = 0;
        m_V3dView->Size(width, height);
        return std::min(width, height) / 10.0;
    }
    return 10.0;
}

void Viewport::setDpiScale(double dpiScale)
{
    if(m_DpiScale != dpiScale)
    {
        m_DpiScale = dpiScale;
        sig_ViewportChanged(this);
    }
}

gp_Pnt Viewport::eyePoint()
{
    if(!m_V3dView.IsNull())
    {
        double xEye = 0, yEye = 0, zEye = 0;
        m_V3dView->Eye(xEye, yEye, zEye);
        m_EyePoint = gp_Pnt(xEye, yEye, zEye);
    }
    return m_EyePoint;
}

void Viewport::setEyePoint(const gp_Pnt& point)
{
    m_EyePoint = point;
    if(!m_V3dView.IsNull())
    {
        m_V3dView->SetEye(point.X(), point.Y(), point.Z());
        sig_ViewportChanged(this);
    }
}

gp_Pnt Viewport::targetPoint()
{
    if(!m_V3dView.IsNull())
    {
        double xAt = 0, yAt = 0, zAt = 0;
        m_V3dView->At(xAt, yAt, zAt);
        m_TargetPoint = gp_Pnt(xAt, yAt, zAt);
    }
    return m_TargetPoint;
}

void Viewport::setTargetPoint(const gp_Pnt& point)
{
    m_TargetPoint = point;
    if(!m_V3dView.IsNull())
    {
        m_V3dView->SetAt(point.X(), point.Y(), point.Z());
        sig_ViewportChanged(this);
    }
}

double Viewport::twist()
{
    if(!m_V3dView.IsNull())
    {
        m_Twist = m_V3dView->Twist() * 180.0 / M_PI; // 转换为度
    }
    return m_Twist;
}

void Viewport::setTwist(double value)
{
    if(!m_V3dView.IsNull())
    {
        m_V3dView->SetTwist(value * M_PI / 180.0); // 转换为弧度
        if(m_Twist != value)
        {
            m_Twist = value;
            sig_ViewportChanged(this);
        }
    }
}

double Viewport::scale()
{
    if(!m_V3dView.IsNull())
    {
        m_Scale = m_V3dView->Scale();
    }
    return m_Scale;
}

void Viewport::setScale(double value)
{
    if(value > 0 && !m_V3dView.IsNull())
    {
        m_V3dView->SetScale(value);
        if(m_Scale != value)
        {
            m_Scale = value;
            sig_ViewportChanged(this);
        }
    }
}

gp_Dir Viewport::getUpDirection() const
{
    if(!m_V3dView.IsNull())
    {
        double xUp = 0, yUp = 0, zUp = 0;
        m_V3dView->Up(xUp, yUp, zUp);
        return gp_Dir(xUp, yUp, zUp);
    }
    return gp_Dir(0, 0, 1); // 默认上方向
}

gp_Dir Viewport::getViewDirection() const
{
    if(!m_V3dView.IsNull())
    {
        gp_Vec eyeVector(m_TargetPoint, m_EyePoint);
        return gp_Dir(eyeVector);
    }
    return gp_Dir(0, 0, -1); // 默认视角方向
}

gp_Dir Viewport::getRightDirection() const
{
    auto upDir = getUpDirection();
    auto viewDir = getViewDirection();
    return upDir.Crossed(viewDir);
}

bool Viewport::screenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt)
{
    if(m_V3dView.IsNull() || !m_V3dView->IfWindow())
    {
        resultPnt = gp_Pnt();
        return false;
    }

    try
    {
        double xv = 0, yv = 0, zv = 0;
        double vx = 0, vy = 0, vz = 0;
        m_V3dView->Convert(screenX, screenY, xv, yv, zv);
        m_V3dView->Proj(vx, vy, vz);

        gp_Lin line(gp_Pnt(xv, yv, zv), gp_Dir(vx, vy, vz));
        IntAna_IntConicQuad intersection(line, plane, Precision::Angular());

        if(intersection.IsDone() && !intersection.IsParallel() && intersection.NbPoints() > 0)
        {
            resultPnt = intersection.Point(1);
            return true;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "screenToPoint exception: " << e.what() << std::endl;
    }

    resultPnt = gp_Pnt();
    return false;
}

void Viewport::updateRenderMode()
{
    if(m_V3dView.IsNull())
    {
        return;
    }

    m_V3dView->SetComputedMode(m_RenderMode == RenderModes::HLR);
    auto& renderParams = m_V3dView->ChangeRenderingParams();

    if(m_RenderMode == RenderModes::Raytraced)
    {
        renderParams.Method = Graphic3d_RM_RAYTRACING;
    }
    else
    {
        renderParams.Method = Graphic3d_RM_RASTERIZATION;
    }

    m_V3dView->Redraw();
    sig_ViewportChanged(this);
}

void Viewport::setRenderMode(RenderModes mode)
{
    if(m_RenderMode != mode)
    {
        m_RenderMode = mode;
        updateRenderMode();
    }
}

void Viewport::resize()
{
    if(!m_V3dView.IsNull())
    {
        m_V3dView->MustBeResized();
        m_V3dView->Redraw();
        sig_ViewportChanged(this);
    }
}
