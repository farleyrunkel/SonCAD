// Copyright [2024] SunCAD

#include "Iact/HudElements/HudContainer.h"

#include <QVBoxLayout>

#include "Iact/HudElements/HudElement.h"

// virtual void SetCursor(QObject* owner, Cursor* cursor)  {}

HudContainer::HudContainer(QWidget* parent) : QWidget(parent) {
	setAutoFillBackground(true);
	setFixedSize(60, 40);
	setMouseTracking(true);
	setHidden(true);
	setLayout(new QVBoxLayout);
}

void HudContainer::AddElement(HudElement* element) {
	layout()->addWidget(element);
	_HudElements.append(element);
}

void HudContainer::SetHintMessage(const QString& message) {
	if (_HintMessage != message) {
		_HintMessage = message;
		emit HintMessageChanged(message);
	}
}
