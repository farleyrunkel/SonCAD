// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_MARKER_H_
#define IACT_VISUAL_MARKER_H_

// Qt includes
#include <QDebug>
#include <QImage>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <QtCore>

// OCCT includes
#include <AIS_Point.hxx>
#include <ElSLib.hxx>
#include <Geom_CartesianPoint.hxx>
#include <gp_Pnt.hxx>
#include <Graphic3d_MarkerImage.hxx>
#include <Image_PixMap.hxx>
#include <Prs3d_PointAspect.hxx>
#include <Quantity_Color.hxx>

// Project includes
#include "Iact/Visual/VisualObject.h"
#include "Occt/OcctExtensions/AIS_PointEx.h"
#include "Occt/OcctHelper/PixMapHelper.h"


class Marker : public VisualObject
{

public:
    enum Styles
    {
        Bitmap = 1,
        Image = 2,
        ModeMask = 0x000f,
        NoClipPlane = 1 << 15,
        Topmost = 1 << 16,
        Background = 1 << 18
    };

    struct MarkerImage
    {
        Handle(Image_PixMap) PixMap;
        int Width;
        int Height;
        Handle(TColStd_HArray1OfByte) Bytes;
    };

public:
    Marker(const std::shared_ptr<WorkspaceController>& workspaceController, Styles styles, const MarkerImage& image);
    Marker(const std::shared_ptr<WorkspaceController>& workspaceController, Styles styles, const QString& imageName, int size);

public:
    void update();
    void set(const gp_Pnt& p);
    void set(const Handle(Geom_CartesianPoint)& p);
    void set(const gp_Pnt2d& p, const gp_Pln& plane);
    void setImage(MarkerImage image);
    Handle(AIS_InteractiveObject) aisObject() const;
    void remove();

    Handle(Prs3d_PointAspect) CreateBitmapPointAspect(const MarkerImage& image, Quantity_Color color);
    Handle(Prs3d_PointAspect) CreateImagePointAspect(const MarkerImage& image);

    bool isSelectable() const;
    void SetSelectable(bool selectable);
    Quantity_Color BackgroundColor() const;
    void SetBackgroundColor(const Quantity_Color& color);
    Quantity_Color Color() const;
    void SetColor(const Quantity_Color& color);

public:
    Marker::MarkerImage& BallImage();
    Marker::MarkerImage& RectImage();
    Marker::MarkerImage& RingImage();
    Marker::MarkerImage& PlusImage();
    Marker::MarkerImage& XImage();
    Marker::MarkerImage& ErrorImage();

private:
    bool ensureAisObject();
    void _UpdatePresentation();
    Marker::MarkerImage _GetMarkerImage(const QString& name, int size);
    Handle(Image_PixMap) _TryGetMarkerAsImage(const QString& name, int size);

private:
    Styles m_styles;
    MarkerImage m_image;
    Handle(AIS_PointEx) _AisPoint = nullptr; // OCCT 点对象
    Handle(Geom_CartesianPoint) m_p; // OCCT 坐标点
    Handle(Prs3d_PointAspect) _PointAspect = nullptr;
    Quantity_Color m_color; // 标记颜色
    Quantity_Color m_colorBg; // 背景颜色
    bool m_isSelectable; // 是否可选择
};

#endif  // IACT_VISUAL_MARKER_H_
