// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_COORD2DHUDELEMENT_H_
#define IACT_HUD_ELEMENTS_COORD2DHUDELEMENT_H_

#include <QWidget>    
#include <QLabel>

#include "Iact/HudElements/HudElement.h"

class Coord2DHudElement : public HudElement
{
    Q_OBJECT
        Q_PROPERTY(double coordinateX READ CoordinateX)
        Q_PROPERTY(double coordinateY READ CoordinateY)
public:
    explicit Coord2DHudElement(QWidget* parent = nullptr);

    double CoordinateX() const { return myCoordinateX; }
    double CoordinateY() const { return myCoordinateY; }

    void SetValues(double coordX, double coordY);

private:
    QLabel* myLabelX;
    QLabel* myLabelY;
    double myCoordinateX;
    double myCoordinateY;
};

#endif  // IACT_HUD_ELEMENTS_COORD2DHUDELEMENT_H_
