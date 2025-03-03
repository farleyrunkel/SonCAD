// Copyright [2024] SunCAD

// Own include
#include "Iact/HudElements/Coord2DHudElement.h"

// Qt includes
#include <QFontMetrics>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>

Coord2DHudElement::Coord2DHudElement(QWidget* parent)
    : HudElement(parent)
    , myLabelX(nullptr)
    , myLabelY(nullptr)
    , myCoordinateX(0.0)
    , myCoordinateY(0.0)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    myLabelX = new QLabel(this);
    myLabelY = new QLabel(this);
    myLabelX->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    myLabelY->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(myLabelX);
    layout->addSpacing(10);
    layout->addWidget(myLabelY);

    setBaseSize(120, 25);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setStyleSheet("color: white; font-size: 12px; background: none;");
    SetValues(0.0, 0.0);
}

void Coord2DHudElement::SetValues(double coordX, double coordY)
{
    myCoordinateX = coordX;
    myCoordinateY = coordY;

    QString xStr = QString::number(myCoordinateX, 'f', 3);
    QString yStr = QString::number(myCoordinateY, 'f', 3);

    myLabelX->setText(xStr);
    myLabelY->setText(yStr);

    adjustSize();
}

