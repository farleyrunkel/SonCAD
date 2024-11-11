// Copyright [2024] SunCAD

#ifndef SRC_IACT_VISUAL_MARKER_H_
#define SRC_IACT_VISUAL_MARKER_H_

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QtCore>

#include <gp_Pnt.hxx>
#include <AIS_Point.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Prs3d_PointAspect.hxx>

#include "Comm/Types/Color.h"
#include "Iact/Visual/VisualObject.h"

class Marker : public VisualObject {
    Q_OBJECT

 public:
     // ʹ�� OCCT ö��
     enum Styles {
         Bitmap = 1,
         Image = 2,
         ModeMask = 0x000f,
         NoClipPlane = 1 << 15,
         Topmost = 1 << 16,
         Background = 1 << 18
     };

 public:
    Marker(WorkspaceController* workspaceController, Styles styles, QImage image)
        : VisualObject(workspaceController, nullptr), _Styles(styles), _Image(image), _Color(Qt::yellow), _ColorBg(Qt::lightGray), _IsSelectable(false),
        _P(nullptr) {
    }

    // ��ȡ/������ɫ
    Color color() const { return _Color; }
    void setColor(const Color& color) {
        if (_Color == color)
            return;
        _Color = color;
        update();
    }

    Color backgroundColor() const { return _ColorBg; }
    void setBackgroundColor(const Color& color) {
        if (_ColorBg == color)
            return;
        _ColorBg = color;
        update();
    }

    bool isSelectable() const { return _IsSelectable; }
    void setSelectable(bool selectable) {
        if (_IsSelectable == selectable)
            return;
        _IsSelectable = selectable;
        update();
    }

    // ���õ�
    void setPoint(const gp_Pnt& point) {
        _P->SetPnt(point);
        update();
    }

    // ����ͼ��
    void setImage(const QImage& image) {
        if (_Image == image)
            return;
        _Image = image;
        update();
    }

    // ������ʾ
    void update() {
        // ȷ�� AIS_Point �������
        if (_AisPoint.IsNull()) {
            _ensureAisObject();
        }
        else {
            _updatePresentation();
            // �� AisContext �Ͻ���������ʾ
            aisContext()->Redisplay(_AisPoint, false);
        }

        if (_IsSelectable) {
            aisContext()->Activate(_AisPoint);
        }
        else {
            aisContext()->Deactivate(_AisPoint);
        }
    }

    // ��ȡ AIS_Object��OCCT��
    Handle(AIS_InteractiveObject) aisObject() const {
        return _AisPoint;
    }

private:
    // ȷ�� _AisPoint ����ȷ��ʼ��
    bool _ensureAisObject() {
        if (_AisPoint.IsNull()) {
            _AisPoint = new AIS_Point(_P);
            // ���õ�λ��
            _AisPoint->SetComponent(_P);
            _AisPoint->SetMarker(Aspect_TOM_USERDEFINED);
        }
        return (!_AisPoint.IsNull());
    }

    // ����չʾ����
    void _updatePresentation() {
        if (_AisPoint.IsNull()) return;

        Prs3d_PointAspect* pointAspect = nullptr;

        //// ���� Styles ���ò�ͬ��չʾЧ��
        //switch (_Styles & Styles::ModeMask) {
        //case Styles::Bitmap:
        //    pointAspect = CreateBitmapPointAspect(_Image, _Color);
        //    break;
        //case Styles::Image:
        //    pointAspect = CreateImagePointAspect(_Image);
        //    break;
        //default:
        //    break;
        //}

        if (pointAspect != nullptr) {
            _AisPoint->Attributes()->SetPointAspect(pointAspect);
            _AisPoint->HilightAttributes()->SetPointAspect(pointAspect);
            _AisPoint->HilightAttributes()->SetColor(Quantity_Color(Colors::Highlight.toQuantityColor()));
            _AisPoint->DynamicHilightAttributes()->SetPointAspect(pointAspect);
            _AisPoint->DynamicHilightAttributes()->SetColor(Quantity_Color(Colors::Highlight.toQuantityColor()));
        }

        if (_Styles & Styles::Background) {
            //_AisPoint->EnableBackground(0.75);
            //_AisPoint->SetColor(_ColorBg.toQuantityColor());
        }
    }

    //// ����ͼ�����ɫ���� Bitmap Point Aspect
    //Handle(Prs3d_PointAspect) CreateBitmapPointAspect(const QImage& image, const Color& color) {
    //    // ʵ�� Bitmap ����ʽ����
    //    return new Prs3d_PointAspect(image, color.toQuantityColor());
    //}

    //// ����ͼ�񴴽���ͨ�� Image Point Aspect
    //Prs3d_PointAspect* CreateImagePointAspect(const QImage& image) {
    //    // ʵ��ͼ�����ʽ����
    //    return new Prs3d_PointAspect(image);
    //}

private:
    Styles _Styles;
    QImage _Image;
    Handle(AIS_Point) _AisPoint = nullptr; // OCCT �����
    Handle(Geom_CartesianPoint) _P; // OCCT �����
    Color _Color; // �����ɫ
    Color _ColorBg; // ������ɫ
    bool _IsSelectable; // �Ƿ��ѡ��
};

#endif  // SRC_IACT_VISUAL_MARKER_H_
