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
    Marker(WorkspaceController* workspaceController, Styles styles, QImage image);

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
    void update();

    // ��ȡ AIS_Object��OCCT��
    Handle(AIS_InteractiveObject) aisObject() const {
        return _AisPoint;
    }

    virtual void remove() {}

private:
    // ȷ�� _AisPoint ����ȷ��ʼ��
    bool _ensureAisObject();

    // ����չʾ����
    void _updatePresentation();

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

    // Static method to load marker images

    static QImage GetMarkerImage(const QString& name, int size)
    {
        //QString cacheName = QString("%1@%2").arg(name).arg(size);

        //// Check if the image is already cached
        //if (_ImageCache.contains(cacheName))
        //{
        //    return _ImageCache.value(cacheName);
        //}

        //// Try to load the marker as a XAML or image (method to load resources)
        //QPixmap pixmap = TryGetMarkerAsXaml(name, size); // Method to load image from XAML
        //if (pixmap.isNull())
        //{
        //    pixmap = TryGetMarkerAsImage(name); // Fallback to loading from an image file
        //}

        //if (pixmap.isNull())
        //{
        //    // Handle error
        //    //MessageBox::Error(QString("Could not load marker image %1 from resource.").arg(name));
        //    _ImageCache.insert(cacheName, QImage());
        //    return QImage(); // Return an empty image on failure
        //}

        // Store image in cache
        QImage image; /*= pixmap.toImage();
        _ImageCache.insert(cacheName, image);*/

        return image;
    }

 public:
    static const QImage BallImage;
    static const QImage RectImage;
    static const QImage RingImage;
    static const QImage PlusImage;
    static const QImage XImage;
    static const QImage ErrorImage;

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
