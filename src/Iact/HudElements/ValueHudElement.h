// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_VALUEHUDELEMENT_H_
#define IACT_HUD_ELEMENTS_VALUEHUDELEMENT_H_

// Qt includes
#include <QDoubleValidator>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

// Project includes
#include "Iact/HudElements/HudElement.h"

class ValueHudElement : public HudElement
{
    Q_OBJECT

public:
    explicit ValueHudElement(const QString& label = "", QWidget* parent = nullptr);

    void SetLabel(const QString& text);
    void SetValue(double value);
    double Value() const;

protected:
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void ValueEntered(double value);

private:
    void OnEditFinished();
    void SimulateKeyPress(QLineEdit* edit, QKeyEvent* event);

private:
    QLabel* myLabel;
    QLineEdit* myEdit;
    bool myIsInKeyboardMode;
};

#endif  // IACT_HUD_ELEMENTS_VALUEHUDELEMENT_H_
