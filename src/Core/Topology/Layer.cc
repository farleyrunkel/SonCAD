// Copyright [2024] SunCAD

#include "Core/Topology/Layer.h"

Sun_Layer::Sun_Layer(QObject* parent)
{
}

// Name Property

QString Sun_Layer::Name() const {
    return _name;
}

void Sun_Layer::SetName(const QString& value) {
    if (_name != value) {
        SaveUndo();
        _name = value;
        emit NameChanged(value);
    }
}

// Visibility Property

bool Sun_Layer::IsVisible() const {
    return _isVisible;
}

void Sun_Layer::SetIsVisible(bool value) {
    if (_isVisible != value) {
        SaveUndo();
        _isVisible = value;
        emit VisibilityChanged(value);
    }
}

void Sun_Layer::SetIsLocked(bool value) {
    if (_isLocked != value) {
        SaveUndo();
        _isLocked = value;
        emit LockStatusChanged(value);
    }
}

// Color Property

QColor Sun_Layer::Color() const {
    return _color;
}

void Sun_Layer::SetColor(const QColor& value) {
    if (_color != value) {
        SaveUndo();
        _color = value;
        emit ColorChanged(value);
    }
}

// Transparency Property

float Sun_Layer::Transparency() const {
    return _transparency;
}

void Sun_Layer::SetTransparency(float value) {
    if (!qFuzzyCompare(_transparency, value)) {
        SaveUndo();
        _transparency = value;
        emit TransparencyChanged(value);
    }
}
