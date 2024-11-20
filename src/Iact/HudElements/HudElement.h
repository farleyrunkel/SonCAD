// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_HUDELEMENT_H_
#define IACT_HUD_ELEMENTS_HUDELEMENT_H_

#include <QWidget>

class Sun_WorkspaceController;

class IHudElement 
{
public:
	 Sun_WorkspaceController* WorkspaceController() const;
	 void setWorkspaceController(Sun_WorkspaceController* controller);

	 virtual void Initialize() = 0;
	 virtual QWidget* Widget() = 0;

private:
	Sun_WorkspaceController* _WorkspaceController;
};

#endif  // IACT_HUD_ELEMENTS_HUDELEMENT_H_
