// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_HUDELEMENT_H_
#define IACT_HUD_ELEMENTS_HUDELEMENT_H_

#include <QWidget>
#include <QSize>

#include "Iact/Workspace/WorkspaceController.h"

class HudElement : public QWidget
{
	Q_OBJECT

public:
	explicit HudElement(QWidget* parent = nullptr)
		: QWidget(parent)
		, myWorkspaceController(nullptr)
	{}

public:
	Handle(WorkspaceController) GetWorkspaceController() const;
	void SetWorkspaceController(const Handle(WorkspaceController)& controller);

	virtual void Initialize() {};

private:
	Handle(WorkspaceController) myWorkspaceController;
};

#endif  // IACT_HUD_ELEMENTS_HUDELEMENT_H_
