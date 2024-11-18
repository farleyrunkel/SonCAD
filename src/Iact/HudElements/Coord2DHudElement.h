// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_COORD2DHUDELEMENT_H_
#define IACT_HUD_ELEMENTS_COORD2DHUDELEMENT_H_

#include <QWidget>    
#include <QLabel>

#include "Iact/HudElements/HudElement.h"

class Coord2DHudElement : public HudElement {
    Q_OBJECT
    Q_PROPERTY(double coordinateX READ CoordinateX)
    Q_PROPERTY(double coordinateY READ CoordinateY)

 public:
    explicit Coord2DHudElement(QWidget* parent = nullptr);

    double CoordinateX() const { return _coordinateX; }
    double CoordinateY() const { return _coordinateY; }

    void SetValues(double coordX, double coordY);

    virtual void initialize() override {};

 signals:
    void CoordinateChanged(double coordX, double coordY);

 private:
    QLabel* m_label;

 private:
    double _coordinateX;
    double _coordinateY;
};

#endif  // IACT_HUD_ELEMENTS_COORD2DHUDELEMENT_H_
