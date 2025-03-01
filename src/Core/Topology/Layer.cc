// Copyright [2024] SunCAD

#include "Core/Topology/Layer.h"


Layer::Layer()
{}

// Name Property

QString Layer::Name() const
{
    return _Name;
}
void Layer::SetName(const QString& value)
{
    if(_Name != value)
    {
        SaveUndo();
        _Name = value;
        _OnNameChanged(value);
    }
}

// Visibility Property

bool Layer::IsVisible() const
{
    return _IsVisible;
}
void Layer::SetIsVisible(bool value)
{
    if(_IsVisible != value)
    {
        SaveUndo();
        _IsVisible = value;
        _OnVisibilityChanged(value);
    }
}

// Lock Status Property

bool Layer::IsLocked() const
{
    return _IsLocked;
}
void Layer::SetIsLocked(bool value)
{
    if(_IsLocked != value)
    {
        SaveUndo();
        _IsLocked = value;
        _OnLockStatusChanged(value);
    }
}

// Color Property

QColor Layer::Color() const
{
    return _Color;
}
void Layer::SetColor(const QColor& value)
{
    if(_Color != value)
    {
        SaveUndo();
        _Color = value;
        _OnColorChanged(value);
    }
}

// Transparency Property

float Layer::Transparency() const
{
    return _Transparency;
}
void Layer::SetTransparency(float value)
{
    if(!qFuzzyCompare(_Transparency, value))
    {
        SaveUndo();
        _Transparency = value;
        _OnTransparencyChanged(value);
    }
}
