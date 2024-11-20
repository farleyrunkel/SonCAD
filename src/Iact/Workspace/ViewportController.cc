// Copyright [2024] SunCAD

#include "Iact/Workspace/ViewportController.h"

Sun_ViewportController::Sun_ViewportController(Sun_Viewport* Viewport, Sun_WorkspaceController* workspacecontroller) 
    : QObject(nullptr),
    m_viewport(Viewport),
    m_workspaceController(workspacecontroller),
    m_viewCube(nullptr),
    m_lockedToPlane(false) {
    init();
}

void Sun_ViewportController::SetWindow(const Handle(Aspect_Window)& theWindow, const Aspect_RenderingContext theContext) {
    if (!View().IsNull()) {
        View()->SetWindow(theWindow, theContext);
    }
}

QString Sun_ViewportController::DumpInfo(bool theIsBasic, bool theToPrint) {
    TCollection_AsciiString anInfo;
    if (!View().IsNull()) {
        TColStd_IndexedDataMapOfStringString aGlCapsDict;
        View()->DiagnosticInformation(aGlCapsDict, theIsBasic
            ? Graphic3d_DiagnosticInfo_Basic
            : Graphic3d_DiagnosticInfo_Complete);
        TColStd_IndexedDataMapOfStringString::Iterator aValueIter(aGlCapsDict);
        for (; aValueIter.More(); aValueIter.Next()) {
            if (!aValueIter.Value().IsEmpty()) {
                if (!anInfo.IsEmpty()) {
                    anInfo += "\n";
                }
                anInfo += aValueIter.Key() + ": " + aValueIter.Value();
            }
        }

        if (theToPrint) {
            Message::SendInfo(anInfo);
        }
    }
    return QString::fromUtf8(anInfo.ToCString());
}

void Sun_ViewportController::mouseMove(const QPointF& pos, Qt::KeyboardModifiers modifiers, MouseMoveMode mode) {
    workspaceController()->mouseMove(this, pos, modifiers);
    workspaceController()->Invalidate();
}

void Sun_ViewportController::mouseDown(Qt::KeyboardModifiers modifiers) {
    workspaceController()->mouseDown(this, modifiers);
    workspaceController()->Invalidate();
}

void Sun_ViewportController::mouseUp(Qt::KeyboardModifiers modifiers) {
    workspaceController()->mouseUp(this, modifiers);
    workspaceController()->Invalidate();
}

void Sun_ViewportController::setPredefinedView(PredefinedViews predefinedView) {
    if (predefinedView == PredefinedViews::WorkingPlane) {
        const auto& plane = workspaceController()->Workspace()->WorkingPlane();
        const auto& dir = plane.Axis().Direction();
        Viewport()->View()->SetProj(dir.X(), dir.Y(), dir.Z());

        const auto& up = plane.YAxis().Direction();
        Viewport()->View()->SetUp(up.X(), up.Y(), up.Z());
        return;
    }

    // 确保视图锁定或无视图立方体时无法进行旋转
    if (m_lockedToPlane || !m_viewCube)
        return;

    V3d_TypeOfOrientation orientation;
    switch (predefinedView) {
    case PredefinedViews::Top:
        orientation = V3d_TypeOfOrientation_Zup_Top;
        break;
    case PredefinedViews::Bottom:
        orientation = V3d_TypeOfOrientation_Zup_Bottom;
        break;
    case PredefinedViews::Left:
        orientation = V3d_TypeOfOrientation_Zup_Left;
        break;
    case PredefinedViews::Right:
        orientation = V3d_TypeOfOrientation_Zup_Right;
        break;
    case PredefinedViews::Front:
        orientation = V3d_TypeOfOrientation_Zup_Front;
        break;
    case PredefinedViews::Back:
        orientation = V3d_TypeOfOrientation_Zup_Back;
        break;
    default:
        return;
    }

    Handle(AIS_ViewCubeOwner) viewCubeOwner = new AIS_ViewCubeOwner(m_viewCube, orientation);
    m_viewCube->HandleClick(viewCubeOwner);
    viewCubeOwner->~AIS_ViewCubeOwner();

    workspaceController()->Invalidate();
}

void Sun_ViewportController::setViewCube(bool isVisible) {
    auto aisContext = workspaceController()->Workspace()->aisContext();

    if (m_viewCube.IsNull())
        return;

    if (isVisible && !aisContext->IsDisplayed(m_viewCube)) {
        aisContext->Display(m_viewCube, false);
        workspaceController()->Invalidate(true);
    }
    else if (!isVisible && aisContext->IsDisplayed(m_viewCube)) {
        aisContext->Remove(m_viewCube, false);
        workspaceController()->Invalidate(true);
    }
}

void Sun_ViewportController::setViewCube(bool isVisible, uint32_t size, double duration) {
    auto aisContext = workspaceController()->Workspace()->aisContext();

    // 如果视图立方体已存在，则使用现有方法更新其显示状态
    if (!m_viewCube.IsNull()) {
        setViewCube(isVisible);
        return;
    }

    // 如果不需要显示视图立方体则直接返回
    if (!isVisible) return;

    //// 加载位图资源
    //auto bitmap = ResourceUtils::readBitmapFromResource("Visual/ViewCubeSides.png");
    //if (bitmap == nullptr) {
    //    Messages::error("Could not load view cube texture from resource.");
    //    return;
    //}

    //// 将位图转换为 PixMap 格式
    //auto pixmap = PixMapHelper::convertFromBitmap(bitmap);
    //if (pixmap == nullptr) {
    //    Messages::error("Could not load view cube texture into pixmap.");
    //    return;
    //}

    // 初始化视图立方体
    m_viewCube = new AIS_ViewCube();
    //m_viewCube->SetSize(size * Viewport::dpiScale());
    //m_viewCube->SetBoxFacetExtension(size * Viewport::dpiScale() * 0.15);
    //m_viewCube->SetViewAnimation(Viewport::aisAnimationCamera());
    m_viewCube->SetFixedAnimationLoop(false);
    m_viewCube->SetDrawAxes(false);
    m_viewCube->SetDuration(duration);
    m_viewCube->SetResetCamera(true);
    m_viewCube->SetFitSelected(true);
    //m_viewCube->SetTexture(pixmap);

    // 设置位置及透视效果
    m_viewCube->SetTransformPersistence(new Graphic3d_TransformPers(
        Graphic3d_TMF_TriedronPers, Aspect_TOTP_RIGHT_UPPER, Graphic3d_Vec2i(100, 100)));

    // 配置颜色
    Quantity_Color sideColor, edgeColor, cornerColor;
    Quantity_Color::ColorFromHex("d9dfe5", sideColor);
    Quantity_Color::ColorFromHex("93a4b6", edgeColor);
    Quantity_Color::ColorFromHex("a6b4c3", cornerColor);

    m_viewCube->BoxSideStyle()->SetColor(sideColor);
    m_viewCube->BoxEdgeStyle()->SetColor(edgeColor);
    m_viewCube->BoxCornerStyle()->SetColor(cornerColor);

    // 设置材质
    auto material = new Graphic3d_MaterialAspect(Graphic3d_NOM_DEFAULT);
    material->SetAmbientColor(Quantity_Color(0.8, 0.8, 0.8, Quantity_TOC_sRGB));
    material->SetDiffuseColor(Quantity_Color(0.2, 0.2, 0.2, Quantity_TOC_sRGB));
    material->SetEmissiveColor(Quantity_NOC_BLACK);
    material->SetSpecularColor(Quantity_NOC_BLACK);
    m_viewCube->SetMaterial(*material);

    // 高亮属性
    auto highlightColor = Colors::Highlight.ToQuantityColor();
    m_viewCube->DynamicHilightAttributes()->ShadingAspect()->SetColor(highlightColor);
    m_viewCube->DynamicHilightAttributes()->ShadingAspect()->SetMaterial(*material);

    //// 显示或隐藏视图立方体
    //if (isVisible) {
    //    aisContext->Display(m_viewCube, false);

    //    for (const auto& viewport : workspaceController()->workspace()->viewports()) {
    //        aisContext->SetViewAffinity(m_viewCube, viewport->v3dView(), viewport.get() == currentViewport().get());
    //    }
    //}

    workspaceController()->Invalidate(true);
}
