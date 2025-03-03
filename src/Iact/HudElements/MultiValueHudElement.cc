// Copyright [2024] SunCAD

// Own include
#include "Iact/HudElements/MultiValueHudElement.h"

// Qt includes
#include <QDoubleValidator>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

// Project includes
#include "Iact/HudElements/HudElement.h"

MultiValueHudElement::MultiValueHudElement(const QString& text1, const QString& text2, QWidget* parent)
    : HudElement(parent)
    , myLabel1(new QLabel(text1, this))
    , myLabel2(new QLabel(text2, this))
    , myEdit1(new QLineEdit("0.0", this))
    , myEdit2(new QLineEdit("0.0", this))
    , myIsInKeyboardMode1(false)
    , myIsInKeyboardMode2(false)
    , myFirstFromKeyboard(true)
{
    // Set up the layout
    auto* layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);

    setLayout(layout);

    // Default styles
    myLabel1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    myLabel1->setStyleSheet("color: white; font-size: 12px; background: none;");

    myLabel2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    myLabel2->setStyleSheet(myLabel1->styleSheet());

    // Set up label and line edits
    myEdit1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    myEdit1->setValidator(new QDoubleValidator(this));

    myEdit2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    myEdit2->setValidator(new QDoubleValidator(this));

    layout->addWidget(myLabel1, 0, 0);
    layout->addWidget(myEdit1, 0, 1);
    layout->addWidget(myLabel2, 1, 0);
    layout->addWidget(myEdit2, 1, 1);

    // Connect signals
    connect(myEdit1, &QLineEdit::editingFinished, this, &MultiValueHudElement::OnEdit1Finished);
    connect(myEdit2, &QLineEdit::editingFinished, this, &MultiValueHudElement::OnEdit2Finished);
}

void MultiValueHudElement::SetLabel(const QString& text1, const QString& text2)
{
    SetLabel1(text1);
    SetLabel2(text2);
}

void MultiValueHudElement::SetLabel1(const QString& text)
{
    myLabel1->setText(text);
}

void MultiValueHudElement::SetLabel2(const QString& text)
{
    myLabel2->setText(text);
}

void MultiValueHudElement::SetValues(double value1, double value2)
{
    SetValue1(value1);
    SetValue2(value2);
}

void MultiValueHudElement::SetValue1(double value)
{
    myEdit1->setText(QString::number(value, 'f', 3));
}

void MultiValueHudElement::SetValue2(double value)
{
    myEdit2->setText(QString::number(value, 'f', 3));
}

void MultiValueHudElement::keyPressEvent(QKeyEvent* event)
{
    if(myIsInKeyboardMode2)
    {
        SimulateKeyPress(myEdit2, event);
        return;
    }

    SimulateKeyPress(myEdit1, event);
    if(event->isAccepted())
    {
        myIsInKeyboardMode1 = true;
        myIsInKeyboardMode2 = false;
    }
}

void MultiValueHudElement::OnEdit1Finished()
{
    myIsInKeyboardMode1 = false;
    myIsInKeyboardMode2 = true;
    myFirstFromKeyboard = true;
}

void MultiValueHudElement::OnEdit2Finished()
{
    myIsInKeyboardMode1 = false;
    myIsInKeyboardMode2 = false;
    myFirstFromKeyboard = true;
    emit MultiValueEntered(myEdit1->text().toDouble(), myEdit2->text().toDouble());
}

void MultiValueHudElement::SimulateKeyPress(QLineEdit* edit, QKeyEvent* event)
{
    if(event->key() == Qt::Key_Backspace)
    {
        edit->backspace();
        event->accept();
    }
    else if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        edit->editingFinished();
        event->accept();
    }
    else
    {
        edit->insert(event->text());
        event->accept();
    }
}
