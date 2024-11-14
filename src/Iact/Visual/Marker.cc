// Copyright [2024] SunCAD

#include "Iact/Visual/Marker.h"

#include "Iact/Workspace/WorkspaceController.h"

Marker::Marker(WorkspaceController* workspaceController, Styles styles, const Handle(Graphic3d_MarkerImage)& image)
    : VisualObject(workspaceController, nullptr), 
    _Styles(styles), 
    _Image(image), 
    _Color(Qt::yellow), 
    _ColorBg(Qt::lightGray), 
    _IsSelectable(false),
    _P(nullptr) {
}

void Marker::update() {
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

Handle(AIS_InteractiveObject) Marker::aisObject() const {
    return _AisPoint;
}

void Marker::remove() {}

Handle(Prs3d_PointAspect) Marker::CreateBitmapPointAspect(const Handle(Graphic3d_MarkerImage)& image, Color color) {
    if (image && image->GetBitMapArray()->IsEmpty()) {
        return new Prs3d_PointAspect(Aspect_TypeOfMarker::Aspect_TOM_BALL, color.toQuantityColor(), 1.0);
    }

    int width = 0;
    int height = 0;
    image->GetTextureSize(width, height);
    return new Prs3d_PointAspect(color.toQuantityColor(), width, height, image->GetBitMapArray());
}

bool Marker::_ensureAisObject() {
    if (_AisPoint.IsNull()) {
        _AisPoint = new AIS_Point(_P);
        // ���õ�λ��
        _AisPoint->SetComponent(_P);
        _AisPoint->SetMarker(Aspect_TOM_USERDEFINED);
    }
    return (!_AisPoint.IsNull());
}

void Marker::_updatePresentation() {
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

Handle(Graphic3d_MarkerImage) Marker::markerImage(const QString& name, int size) {
    auto a = tryGetMarkerAsImage(name, size);
    Handle(Graphic3d_MarkerImage) res;
    if (a) {
        res = new Graphic3d_MarkerImage(a);
    }
    return res;
}

Handle(Image_PixMap) Marker::tryGetMarkerAsImage(const QString& name, int size) {
    int dpiScale = 1;
    int finalSize = static_cast<int>(size * dpiScale);

    QString imagePath = ResourceUtils::iconPath("Marker/" + name);

    QImage image(imagePath);
    if (!image.load(imagePath, "svg")) {
        qDebug() << "Error: Failed to load image:" << imagePath;
        return nullptr;
    }

    Handle(Image_PixMap) pixmap = PixMapHelper::convertFromBitmap(image.scaled(finalSize, finalSize));
    if (pixmap.IsNull()) {
        qDebug() << "Could not load marker image " << name << " into pixmap.";
        return nullptr;
    }
    return pixmap;
}

Handle(Graphic3d_MarkerImage) Marker::plusImage() {
    static Handle(Graphic3d_MarkerImage) RectImage = markerImage("Plus", 16);
    return RectImage;
}

Handle(Graphic3d_MarkerImage) Marker::ballImage() {
    static Handle(Graphic3d_MarkerImage) RectImage = markerImage("Ball", 16);
    return RectImage;
}
