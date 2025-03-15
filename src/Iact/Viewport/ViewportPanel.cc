// Copyright [2024] SunCAD

// Own Libraries
#include "Iact/Viewport/ViewportPanel.h"

// Qt Libraries
#include <QGuiApplication>
#include <QScreen>
#include <QVBoxLayout>
#include <QWidget>
#include <QWindow>

// Project Libraries
#include "Iact/Viewport/ViewportMouseControlDefault.h"
#include "Iact/Workspace/InteractiveContext.h"

ViewportPanel::ViewportPanel(QWidget* parent)
	: QWidget(parent)
	, _MouseControl(new ViewportMouseControlDefault())
	, _HudContainer(new QFrame(this))
	, _ViewportHwndHost(nullptr)
	, _MouseMovePosition(0.0, 0.0)
{
	Message::SendInfo("ViewportPanel: Constructing ViewportPanel");

	_HudContainer->setFrameShape(QFrame::NoFrame);
	_HudContainer->setMouseTracking(true);
	_HudContainer->setVisible(false);
	_HudContainer->setLayout(new QVBoxLayout);

	_HudContainer->setAutoFillBackground(false);
	_HudContainer->setStyleSheet("background-color: rgba(128, 128, 128, 0.5);");

	setLayout(new QVBoxLayout(this));
	setMouseTracking(true);

	_ViewportControllerChanged();

	_HudContainer->raise();
}

void ViewportPanel::mouseMoveEvent(QMouseEvent* event)
{
	qDebug() << "ViewportPanel: Mouse move event";
	QWidget::mouseMoveEvent(event);

	_MouseMovePosition = this->mapFromGlobal(event->globalPos());

	if(_ViewportHwndHost)
	{
		auto p = _ViewportHwndHost->mapFromParent(_MouseMovePosition);
		_MouseControl->MouseMove(p, event, event->modifiers());
	}
	_HudContainer->adjustSize();
	_HudContainer->update();  // 强制重新绘制控件
	updateHud(_MouseMovePosition);
}

void ViewportPanel::wheelEvent(QWheelEvent* event)
{
	QWidget::wheelEvent(event);
}

void ViewportPanel::mousePressEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);
	_MouseMovePosition = this->mapFromGlobal(event->globalPos());

	setFocus();

	//if(_ViewportHwndHost)
	//{
	//	auto p = _ViewportHwndHost->mapFromParent(_MouseMovePosition);
	//	_MouseControl->MouseDown(p, event->button(), 1, event->buttons(), event->modifiers());
	//}
}

void ViewportPanel::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
}

void ViewportPanel::mouseReleaseEvent(QMouseEvent* event)
{
	QWidget::mouseReleaseEvent(event);
	_MouseMovePosition = this->mapFromGlobal(event->globalPos());

	//if(_ViewportHwndHost)
	//{
	//	auto p = _ViewportHwndHost->mapFromParent(_MouseMovePosition);
	//	_MouseControl->MouseUp(p, event->button(), event->buttons(), event->modifiers());
	//}
	_HudContainer->adjustSize();
	_HudContainer->update();
	updateHud(_MouseMovePosition);
}


// 重载 contextMenuEvent 以显示右键菜单

void ViewportPanel::contextMenuEvent(QContextMenuEvent* event)
{
	qDebug() << "ViewportPanel: Context menu event";
	// 创建一个 QMenu 对象
	QMenu contextMenu(this);

	// 创建菜单项并连接槽函数
	QAction* action1 = contextMenu.addAction("Option 1");
	QAction* action2 = contextMenu.addAction("Option 2");

	// 显示菜单
	contextMenu.exec(event->globalPos());
}

void ViewportPanel::model_PropertyChanged(const QString& propertyName)
{
	if(propertyName == "viewportController")
	{
		_ViewportControllerChanged();
	}
	if(propertyName == "hintMessage")
	{

	}
}

void ViewportPanel::_ViewportControllerChanged()
{
	Message::SendInfo("ViewportPanel: ViewportController changed");
	//auto viewportController = m_dataContext->viewportController();

	//if(viewportController == nullptr)
	//	return;

	//if(_MouseControl != nullptr)
	//{
	//	_MouseControl->setViewportController(viewportController);
	//}

	auto VC = InteractiveContext::Current()->GetViewportController();

	auto newHost = new ViewportHwndHost(new ViewportController, this);
	newHost->setFocus();

	if(_ViewportHwndHost != nullptr)
	{
		layout()->replaceWidget(_ViewportHwndHost, newHost);
		delete _ViewportHwndHost;
	}
	else
	{
		layout()->addWidget(newHost);
	}
	_ViewportHwndHost = newHost;
	//_HudContainer->raise();
}

void ViewportPanel::updateHud(const QPointF& pos)
{
	int x = pos.x() + 10;
	int y = pos.y() - 10 - _HudContainer->height();
	_HudContainer->move(x, y);
}