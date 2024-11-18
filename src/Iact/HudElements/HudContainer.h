// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_HUDCONATAINER_H_
#define IACT_HUD_ELEMENTS_HUDCONATAINER_H_

#include <QWidget>
#include <QMouseEvent>


class HudContainer : public QWidget 
{
	Q_OBJECT
public:
	explicit HudContainer(QWidget* parent = nullptr) : QWidget(parent) {
		setAutoFillBackground(true);
		setFixedSize(60, 40);
		setMouseTracking(true);
	}

protected:
	virtual void mouseMoveEvent(QMouseEvent* theEvent) override {
		emit MouseMoved(theEvent->x(), theEvent->y());
	}

signals:
	void MouseMoved(int x, int y);
};

#endif  // IACT_HUD_ELEMENTS_HUDCONATAINER_H_
