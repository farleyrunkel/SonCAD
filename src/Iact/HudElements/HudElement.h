// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_HUDELEMENT_H_
#define IACT_HUD_ELEMENTS_HUDELEMENT_H_

#include <QWidget>

class WorkspaceController;

class IHudElement {
 public:
	 virtual ~IHudElement() = default;

	 WorkspaceController* workspaceController() const;

	 virtual void Initialize() = 0;
	 virtual QWidget* Widget() = 0;

private:
	WorkspaceController* m_workspaceController;
};

#endif  // IACT_HUD_ELEMENTS_HUDELEMENT_H_
