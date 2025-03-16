// Copyright [2024] SunCAD

#ifndef IACT_VIEWPORT_VIEWPORTPANEL_H_
#define IACT_VIEWPORT_VIEWPORTPANEL_H_

// stl includes
#include <functional>
#include <memory>
#include <string>

// Qt includes
#include <QAction>
#include <QDebug>
#include <QFrame>
#include <QMenu>
#include <QPointF>
#include <QWidget>

// Project includes
#include "Iact/Viewport/ViewportHwndHost.h"
#include "Iact/Viewport/ViewportMouseControl.h"

/// @brief ViewportPanel class
class ViewportPanel : public QWidget
{
	Q_OBJECT

public:
	explicit ViewportPanel(QWidget* parent = nullptr);

	~ViewportPanel() override {}

public:

protected:
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	virtual void wheelEvent(QWheelEvent* event) override;
	virtual void keyPressEvent(QKeyEvent* event) override {}
	virtual void keyReleaseEvent(QKeyEvent* event) override {}
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void contextMenuEvent(QContextMenuEvent* event) override;

private:
	void model_PropertyChanged(const std::string& propertyName);
	void _ViewportControllerChanged();
	void updateHud(const QPointF& pos);

private:
	ViewportHwndHost* _ViewportHwndHost;
	ViewportMouseControl* _MouseControl;
	QFrame* _HudContainer;
	QPointF _MouseMovePosition;
	bool _SuppressContextMenu;
	bool _ContextMenuIsOpen;
};

#endif  // IACT_VIEWPORT_VIEWPORTPANEL_H_