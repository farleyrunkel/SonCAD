#ifndef m_Viewport_h_
#define m_Viewport_h_

#include <boost/signals2.hpp>

#include <AIS_InteractiveContext.hxx>
#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <gp_Lin.hxx>
#include <IntAna_IntConicQuad.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_AnimationCamera.hxx>
#include <Graphic3d_Vec2.hxx>
#include <Quantity_Color.hxx>
#include <Precision.hxx>

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
    Viewport() {}
    explicit Viewport(const std::shared_ptr<Workspace>& workspace);
    ~Viewport(); // 添加析构函数

    // 视口视图访问
    Handle(V3d_View) view() const { return m_V3dView; }
    Handle(V3d_View) v3dView() const { return m_V3dView; }
    std::shared_ptr<Workspace> workspace() const { return m_Workspace; }
    Handle(AIS_AnimationCamera) aisAnimationCamera() const { return m_AnimationCamera; }

    // 像素和尺寸相关
    double pixelSize() const;
    Graphic3d_Vec2d size() const;
    Graphic3d_Vec2i screenSize() const;
    double gizmoScale() const;

    // DPI缩放
    double dpiScale() const { return m_DpiScale; }
    void setDpiScale(double dpiScale);

    // 相机属性 getter 和 setter
    gp_Pnt eyePoint();
    void setEyePoint(const gp_Pnt& point);
    gp_Pnt targetPoint();
    void setTargetPoint(const gp_Pnt& point);
    double twist();
    void setTwist(double value);
    double scale();
    void setScale(double value);

    // 方向向量
    gp_Dir getUpDirection() const;
    gp_Dir getViewDirection() const;
    gp_Dir getRightDirection() const;

    // 初始化和功能方法
    void init(bool useMsaa);
    bool screenToPoint(gp_Pln plane, int screenX, int screenY, gp_Pnt& resultPnt);
    void updateRenderMode();
    void resize();

    // 渲染模式
    RenderModes renderMode() const { return m_RenderMode; }
    void setRenderMode(RenderModes mode);

public:
    static boost::signals2::signal<void(Viewport*)> sig_ViewportChanged;

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
    double m_Twist = 0.0;
    double m_Scale = 100.0;
    double m_DpiScale = 1.0;

    bool m_NeedsRedraw = false;
    bool m_NeedsImmediateRedraw = false;
};

#endif // !m_Viewport_h_