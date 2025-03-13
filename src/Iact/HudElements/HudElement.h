// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_HUDELEMENT_H_
#define IACT_HUD_ELEMENTS_HUDELEMENT_H_

#include <QWidget>
#include <QSize>

#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>

class WorkspaceController;

class IHudElement : public QWidget
{
	Q_OBJECT

public:
	explicit IHudElement(QWidget* parent) : QWidget(parent)
	{}

public:
	Handle(WorkspaceController) GetWorkspaceController() const;
	void setWorkspaceController(const Handle(WorkspaceController)& controller);

	virtual void Initialize() = 0;

signals:
	void WidthChanged(int);
	void HeightChanged(int);

private:
	Handle(WorkspaceController) _WorkspaceController;
};

#endif  // IACT_HUD_ELEMENTS_HUDELEMENT_H_
