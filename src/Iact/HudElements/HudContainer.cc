// Copyright [2024] SunCAD

#include "Iact/HudElements/HudContainer.h"

#include <QVBoxLayout>
#include "QApplication"

#include "Iact/HudElements/HudElement.h"
// virtual void SetCursor(QObject* owner, Cursor* cursor)  {}

HudContainer::HudContainer(QWidget* parent)
    : QFrame(parent) {
    setAutoFillBackground(true); // ���Զ���䱳��
    setFixedSize(100, 28);
    setMouseTracking(true);
    setFrameShape(NoFrame);
    //setAttribute(Qt::WA_TranslucentBackground); // ����͸������
    setHidden(false) ;

    setLayout(new QVBoxLayout);
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setAlignment(Qt::AlignCenter);

    // ������ʽ��Ϊ��ɫ��͸��
    setStyleSheet("background-color: rgba(128, 128, 128, 128);"); // ��͸����ɫ
}


void HudContainer::AddElement(IHudElement* element) {
	layout()->addWidget(element->Widget());
	_HudElements.append(element);
}

void HudContainer::SetHintMessage(const QString& message) {
	if (_HintMessage != message) {
		_HintMessage = message;
		emit HintMessageChanged(message);
	}
}