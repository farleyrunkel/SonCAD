// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
#define SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_

#include <QObject>
#include <QVector>

#include "Iact/HudElements/HudElement.h"
#include "Iact/Workspace/WorkspaceController.h"

class WorkspaceControl : public QObject {
	Q_OBJECT

 public:
	explicit WorkspaceControl(QObject* parent = nullptr);

	WorkspaceController* workspaceController() const;;
	void setWorkspaceController(WorkspaceController* workspaceController) {
		m_workspaceController = workspaceController;
	}

 private: 
	WorkspaceController* m_workspaceController;
	QVector<HudElement*> m_hudElements;

};

#endif  // SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
