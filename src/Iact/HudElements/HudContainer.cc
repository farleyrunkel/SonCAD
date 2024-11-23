// Copyright [2024] SunCAD

#include "Iact/HudElements/HudContainer.h"

#include <QVBoxLayout>
#include "QApplication"

#include "Iact/HudElements/HudElement.h"
// virtual void SetCursor(QObject* owner, Cursor* cursor)  {}

HudContainer::HudContainer(QWidget* parent)
    : QFrame(parent) {
    setAutoFillBackground(true); // 不自动填充背景
    setFixedSize(110, 28);
    setMouseTracking(true);
    setFrameShape(NoFrame);
    // setAttribute(Qt::WA_TranslucentBackground); // 启用透明背景
    setHidden(false) ;

    setLayout(new QVBoxLayout);
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setAlignment(Qt::AlignCenter);

    // 设置样式表为灰色半透明
    setStyleSheet("background-color: rgba(128, 128, 128, 128);"); // 半透明灰色
}


void HudContainer::AddElement(IHudElement* element) {
	layout()->addWidget(element->Widget());
	_HudElements.append(element);
    adjustSize();
}

void HudContainer::SetHintMessage(const QString& message) {
	if (_HintMessage != message) {
		_HintMessage = message;
		emit HintMessageChanged(message);
	}
}
