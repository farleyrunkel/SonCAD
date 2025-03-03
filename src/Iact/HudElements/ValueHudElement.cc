// Copyright [2024] SunCAD

// Own include
#include "Iact/HudElements/ValueHudElement.h"

// Qt includes
#include <QDoubleValidator>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

ValueHudElement::ValueHudElement(const QString& label, QWidget* parent)
    : HudElement(parent)
    , myLabel(new QLabel(label, this))
    , myEdit(new QLineEdit("0.0", this))
    , myIsInKeyboardMode(false)
{
    // 设置布局
    auto* layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);
    setLayout(layout);

    // 默认样式
    myLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    myLabel->setStyleSheet("color: white; font-size: 12px; background: none;");

    myEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    myEdit->setValidator(new QDoubleValidator(this));

    layout->addWidget(myLabel, 0, 0);
    layout->addWidget(myEdit, 0, 1);

    // 连接信号
    connect(myEdit, &QLineEdit::editingFinished, this, &ValueHudElement::OnEditFinished);
}

void ValueHudElement::SetLabel(const QString& text)
{
    myLabel->setText(text);
}

void ValueHudElement::SetValue(double value)
{
    myEdit->setText(QString::number(value, 'f', 3));
}

double ValueHudElement::Value() const
{
    return myEdit->text().toDouble();
}

void ValueHudElement::keyPressEvent(QKeyEvent* event)
{
    SimulateKeyPress(myEdit, event);
    if(event->isAccepted())
    {
        myIsInKeyboardMode = true;
    }
}

void ValueHudElement::OnEditFinished()
{
    myIsInKeyboardMode = false;
    emit ValueEntered(myEdit->text().toDouble());
}

void ValueHudElement::SimulateKeyPress(QLineEdit* edit, QKeyEvent* event)
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
