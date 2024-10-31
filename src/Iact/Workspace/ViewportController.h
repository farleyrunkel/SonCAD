// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

#include <QObject>

#include <Aspect_NeutralWindow.hxx>
#include <Aspect_RenderingContext.hxx>
#include <Standard_Integer.hxx>
#include <V3d_View.hxx>
#include <AIS_ViewCube.hxx>
#include <V3d_TypeOfOrientation.hxx>
#include <Graphic3d_MaterialAspect.hxx>

#include "Core/Viewport.h"
#include "Iact/Workspace/WorkspaceController.h"

class ViewportController : public QObject {
    Q_OBJECT

public:
    explicit ViewportController(QObject* parent = nullptr) : QObject(parent) {}

    Viewport* viewport() const { return m_viewport; }

    Handle(V3d_View) view() const {
        return this->viewport() ? this->viewport()->view() : nullptr;
    }

    Handle(AIS_ViewCube) viewCube() const {
        return m_viewCube;
    }

    const Handle(Aspect_Window)& window() const {
        return !view().IsNull() ? view()->Window() : nullptr;
    }

    void setWindow(const Handle(Aspect_Window)& theWindow,
        const Aspect_RenderingContext theContext = NULL);

     QString dumpInfo(bool theIsBasic, bool theToPrint);

     WorkspaceController* workspaceController() const { return m_workspaceController; }

     enum class PredefinedViews {
         Top,
         Bottom,
         Left,
         Right,
         Front,
         Back,
         WorkingPlane
     };

     //--------------------------------------------------------------------------------------------------

     void setPredefinedView(PredefinedViews predefinedView) {

         if (predefinedView == PredefinedViews::WorkingPlane) {
             const auto& plane = workspaceController()->workspace()->workingPlane();
             const auto& dir = plane.Axis().Direction();
             viewport()->view()->SetProj(dir.X(), dir.Y(), dir.Z());

             const auto& up = plane.YAxis().Direction();
             viewport()->view()->SetUp(up.X(), up.Y(), up.Z());
             return;
         }

         // ȷ����ͼ����������ͼ������ʱ�޷�������ת
         if (_LockedToPlane || !m_viewCube)
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

         workspaceController()->invalidate();
     }

private:
    void setViewCube(bool isVisible) {
        auto aisContext = workspaceController()->workspace()->aisContext();

        if (m_viewCube.IsNull())
            return;

        if (isVisible && !aisContext->IsDisplayed(m_viewCube)) {
            aisContext->Display(m_viewCube, false);
            workspaceController()->invalidate(true);
        }
        else if (!isVisible && aisContext->IsDisplayed(m_viewCube)) {
            aisContext->Remove(m_viewCube, false);
            workspaceController()->invalidate(true);
        }
    }

    void setViewCube(bool isVisible, uint32_t size, double duration) {
        auto aisContext = workspaceController()->workspace()->aisContext();

        // �����ͼ�������Ѵ��ڣ���ʹ�����з�����������ʾ״̬
        if (!m_viewCube.IsNull()) {
            setViewCube(isVisible);
            return;
        }

        // �������Ҫ��ʾ��ͼ��������ֱ�ӷ���
        if (!isVisible) return;

        //// ����λͼ��Դ
        //auto bitmap = ResourceUtils::readBitmapFromResource("Visual/ViewCubeSides.png");
        //if (bitmap == nullptr) {
        //    Messages::error("Could not load view cube texture from resource.");
        //    return;
        //}

        //// ��λͼת��Ϊ PixMap ��ʽ
        //auto pixmap = PixMapHelper::convertFromBitmap(bitmap);
        //if (pixmap == nullptr) {
        //    Messages::error("Could not load view cube texture into pixmap.");
        //    return;
        //}

        // ��ʼ����ͼ������
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

        // ����λ�ü�͸��Ч��
        m_viewCube->SetTransformPersistence(new Graphic3d_TransformPers(
            Graphic3d_TMF_TriedronPers, Aspect_TOTP_RIGHT_UPPER, Graphic3d_Vec2i(100, 100)));

        // ������ɫ
        Quantity_Color sideColor, edgeColor, cornerColor;
        Quantity_Color::ColorFromHex("d9dfe5", sideColor);
        Quantity_Color::ColorFromHex("93a4b6", edgeColor);
        Quantity_Color::ColorFromHex("a6b4c3", cornerColor);

        m_viewCube->BoxSideStyle()->SetColor(sideColor);
        m_viewCube->BoxEdgeStyle()->SetColor(edgeColor);
        m_viewCube->BoxCornerStyle()->SetColor(cornerColor);

        // ���ò���
        auto material = new Graphic3d_MaterialAspect(Graphic3d_NOM_DEFAULT);
        material->SetAmbientColor(Quantity_Color(0.8, 0.8, 0.8, Quantity_TOC_sRGB));
        material->SetDiffuseColor(Quantity_Color(0.2, 0.2, 0.2, Quantity_TOC_sRGB));
        material->SetEmissiveColor(Quantity_NOC_BLACK);
        material->SetSpecularColor(Quantity_NOC_BLACK);
        m_viewCube->SetMaterial(*material);

        // ��������
        auto highlightColor = Colors::Highlight.toQuantityColor();
        m_viewCube->DynamicHilightAttributes()->ShadingAspect()->SetColor(highlightColor);
        m_viewCube->DynamicHilightAttributes()->ShadingAspect()->SetMaterial(*material);

        //// ��ʾ��������ͼ������
        //if (isVisible) {
        //    aisContext->Display(m_viewCube, false);

        //    for (const auto& viewport : workspaceController()->workspace()->viewports()) {
        //        aisContext->SetViewAffinity(m_viewCube, viewport->v3dView(), viewport.get() == currentViewport().get());
        //    }
        //}

        workspaceController()->invalidate(true);
    }

private:
    Viewport* m_viewport = nullptr;
    Handle(AIS_ViewCube) m_viewCube = nullptr;
    bool _LockedToPlane = false;

private:
    WorkspaceController* m_workspaceController = nullptr;
};
#endif // SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
