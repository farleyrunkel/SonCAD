// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_MULTIVALUEHUDELEMENT_H_
#define IACT_HUD_ELEMENTS_MULTIVALUEHUDELEMENT_H_

// Qt includes
#include <QDoubleValidator>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

// Project includes
#include "Iact/HudElements/HudElement.h"

class MultiValueHudElement : public HudElement
{
    Q_OBJECT

public:
    explicit MultiValueHudElement(const QString& text1 = "", const QString& text2 = "", QWidget* parent = nullptr);

    void SetLabel(const QString& text1, const QString& text2);
    void SetLabel1(const QString& text);
    void SetLabel2(const QString& text);
    void SetValues(double value1, double value2);
    void SetValue1(double value);
    void SetValue2(double value);

protected:
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void MultiValueEntered(double value1, double value2);

private:
    void OnEdit1Finished();
    void OnEdit2Finished();
    void SimulateKeyPress(QLineEdit* edit, QKeyEvent* event);

private:
    QLabel* myLabel1;
    QLabel* myLabel2;
    QLineEdit* myEdit1;
    QLineEdit* myEdit2;
    bool myIsInKeyboardMode1;
    bool myIsInKeyboardMode2;
    bool myFirstFromKeyboard;
};

#endif  // IACT_HUD_ELEMENTS_MULTIVALUEHUDELEMENT_H_
