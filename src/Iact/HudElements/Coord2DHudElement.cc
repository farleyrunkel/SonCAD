// Copyright [2024] SunCAD

#include "Iact/HudElements/Coord2DHudElement.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QString>

Coord2DHudElement::Coord2DHudElement(QWidget* parent)
    : HudElement(parent), _coordinateX(0.0), _coordinateY(0.0) 
{
    setLayout(new QHBoxLayout(this));

    m_label = new QLabel(this);

    connect(this, &Coord2DHudElement::CoordinateChanged, m_label, [this]() {
        QString xStr = QString::number(_coordinateX, 'f', 3);
        QString yStr = QString::number(_coordinateY, 'f', 3);
        m_label->setText(xStr + " " + yStr);
        m_label->adjustSize();
    });

    layout()->addWidget(m_label);
}

void Coord2DHudElement::SetValues(double coordX, double coordY) {
    _coordinateX = coordX;
    _coordinateY = coordY;
    emit CoordinateChanged(coordX, coordY);
}
