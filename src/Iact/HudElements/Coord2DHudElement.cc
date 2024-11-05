// Copyright [2024] SunCAD

#include "Iact/HudElements/Coord2DHudElement.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QString>

Coord2DHudElement::Coord2DHudElement(QWidget* parent)
    : HudElement(parent), _coordinateX(0.0), _coordinateY(0.0) {
    auto layout = new QHBoxLayout(this);
    setLayout(layout);

    m_label = new QLabel(this);
    connect(this, &Coord2DHudElement::coordinateXChanged, m_label, [this]() {
        QString xStr = QString::number(_coordinateX, 'f', 3);
        QString yStr = QString::number(_coordinateY, 'f', 3);
        m_label->setText(xStr + "   " + yStr);
        m_label->adjustSize();
    });

    layout->addWidget(m_label);
}

void Coord2DHudElement::setCoordinateX(double x) {
    if (_coordinateX != x) {
        _coordinateX = x;
        emit coordinateXChanged();
    }
}

void Coord2DHudElement::setCoordinateY(double y) {
    if (_coordinateY != y) {
        _coordinateY = y;
        emit coordinateYChanged();
    }
}

void Coord2DHudElement::setValues(double coordX, double coordY) {
    setCoordinateX(coordX);
    setCoordinateY(coordY);
}
