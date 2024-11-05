// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_HUDELEMENT_H_
#define IACT_HUD_ELEMENTS_HUDELEMENT_H_

#include <QWidget>

class WorkspaceController;

class HudElement : public QWidget {
 public:
	 explicit HudElement(QWidget* parent = nullptr);
	 WorkspaceController* workspaceController() const;

	 virtual void initialize() = 0;

private:
	WorkspaceController* m_workspaceController;
};

#endif  // IACT_HUD_ELEMENTS_HUDELEMENT_H_
