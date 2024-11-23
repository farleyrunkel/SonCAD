// Copyright [2024] SunCAD

#include "Iact/HudElements/Coord2DHudElement.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QString>

Coord2DHudElement::Coord2DHudElement(QWidget* parent)
    : QLabel(parent), _CoordinateX(0.0), _CoordinateY(0.0)
{
    Initialize();
}


void Coord2DHudElement::SetValues(double coordX, double coordY) 
{
    _CoordinateX = coordX;
    _CoordinateY = coordY;
    QString xStr = QString::number(_CoordinateX, 'f', 3);
    QString yStr = QString::number(_CoordinateY, 'f', 3);
    setText(xStr + "   " + yStr);
    adjustSize();
}

void Coord2DHudElement::Initialize()
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("color: white; font-size: 12px; background: none;");
}
