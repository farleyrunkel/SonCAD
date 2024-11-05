// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_COORD2DHUDELEMENT_H_
#define IACT_HUD_ELEMENTS_COORD2DHUDELEMENT_H_

#include <QWidget>    
#include <QLabel>

#include "Iact/HudElements/HudElement.h"

class Coord2DHudElement : public HudElement {
    Q_OBJECT
    Q_PROPERTY(double coordinateX READ getCoordinateX WRITE setCoordinateX)
    Q_PROPERTY(double coordinateY READ getCoordinateY WRITE setCoordinateY)

public:
    explicit Coord2DHudElement(QWidget* parent = nullptr);

    double getCoordinateX() const { return _coordinateX; }
    double getCoordinateY() const { return _coordinateY; }

    void setCoordinateX(double x);
    void setCoordinateY(double y);

    Q_INVOKABLE void setValues(double coordX, double coordY);

signals:
    void coordinateXChanged();
    void coordinateYChanged();

private:
    double _coordinateX;
    double _coordinateY;

    QLabel* m_label;
};

#endif  // IACT_HUD_ELEMENTS_COORD2DHUDELEMENT_H_
