// Copyright [2024] SunCAD

#include "Iact/Visual/Marker.h"

Marker::Marker(WorkspaceController* workspaceController, Styles styles, QImage image)
    : VisualObject(workspaceController, nullptr), _Styles(styles), _Image(image), _Color(Qt::yellow), _ColorBg(Qt::lightGray), _IsSelectable(false),
    _P(nullptr) {
}

// 更新展示设置


// 确保 _AisPoint 被正确初始化


// 更新显示

void Marker::update() {
    // 确保 AIS_Point 对象存在
    if (_AisPoint.IsNull()) {
        _ensureAisObject();
    }
    else {
        _updatePresentation();
        // 在 AisContext 上进行重新显示
        aisContext()->Redisplay(_AisPoint, false);
    }

    if (_IsSelectable) {
        aisContext()->Activate(_AisPoint);
    }
    else {
        aisContext()->Deactivate(_AisPoint);
    }
}

bool Marker::_ensureAisObject() {
    if (_AisPoint.IsNull()) {
        _AisPoint = new AIS_Point(_P);
        // 设置点位置
        _AisPoint->SetComponent(_P);
        _AisPoint->SetMarker(Aspect_TOM_USERDEFINED);
    }
    return (!_AisPoint.IsNull());
}

void Marker::_updatePresentation() {
    if (_AisPoint.IsNull()) return;

    Prs3d_PointAspect* pointAspect = nullptr;

    //// 根据 Styles 设置不同的展示效果
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

const QImage Marker::BallImage = Marker::GetMarkerImage("Ball", 8);
const QImage Marker::RectImage = Marker::GetMarkerImage("Rect", 8);
const QImage Marker::RingImage = Marker::GetMarkerImage("Ring", 16);
const QImage Marker::PlusImage = Marker::GetMarkerImage("Plus", 16);
const QImage Marker::XImage = Marker::GetMarkerImage("X", 16);
const QImage Marker::ErrorImage = Marker::GetMarkerImage("Error", 24);