// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
#define SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_

#include <QObject>

#include "Iact/Workspace/WorkspaceController.h"

class WorkspaceControl : public QObject {
	Q_OBJECT

 public:
	explicit WorkspaceControl(QObject* parent = nullptr);

	//WorkspaceController* workspaceController() const;
	//void setWorkspaceController(WorkspaceController* controller);

 //private: 
	//WorkspaceController* m_WorkspaceController;
};

#endif  // SRC_IACT_FRAMEWORK_WORKSPACECONTROLL_H_
