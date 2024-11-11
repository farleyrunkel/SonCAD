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
     // 使用 OCCT 枚举
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

    // 获取/设置颜色
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

    // 设置点
    void setPoint(const gp_Pnt& point) {
        _P->SetPnt(point);
        update();
    }

    // 设置图像
    void setImage(const QImage& image) {
        if (_Image == image)
            return;
        _Image = image;
        update();
    }

    // 更新显示
    void update();

    // 获取 AIS_Object（OCCT）
    Handle(AIS_InteractiveObject) aisObject() const {
        return _AisPoint;
    }

    virtual void remove() {}

private:
    // 确保 _AisPoint 被正确初始化
    bool _ensureAisObject();

    // 更新展示设置
    void _updatePresentation();

    //// 根据图像和颜色创建 Bitmap Point Aspect
    //Handle(Prs3d_PointAspect) CreateBitmapPointAspect(const QImage& image, const Color& color) {
    //    // 实现 Bitmap 点样式设置
    //    return new Prs3d_PointAspect(image, color.toQuantityColor());
    //}

    //// 根据图像创建普通的 Image Point Aspect
    //Prs3d_PointAspect* CreateImagePointAspect(const QImage& image) {
    //    // 实现图像点样式设置
    //    return new Prs3d_PointAspect(image);
    //}

private:
    Styles _Styles;
    QImage _Image;
    Handle(AIS_Point) _AisPoint = nullptr; // OCCT 点对象
    Handle(Geom_CartesianPoint) _P; // OCCT 坐标点
    Color _Color; // 标记颜色
    Color _ColorBg; // 背景颜色
    bool _IsSelectable; // 是否可选择
};

#endif  // SRC_IACT_VISUAL_MARKER_H_
