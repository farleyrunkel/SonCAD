// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_HUDELEMENT_H_
#define IACT_HUD_ELEMENTS_HUDELEMENT_H_

#include <QWidget>

#include "Iact/Workspace/WorkspaceController.h"

class HudElement : public QWidget {
 public:
	 explicit HudElement(QWidget* parent = nullptr) : QWidget(parent) {
		 setMinimumHeight(25);
	 }
	 WorkspaceController* workspaceController() const { return m_workspaceController; };

	 virtual void initialize() = 0;

private:
	WorkspaceController* m_workspaceController;
};

#endif  // IACT_HUD_ELEMENTS_HUDELEMENT_H_
