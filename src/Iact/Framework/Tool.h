// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_TOOL_H_
#define SRC_IACT_FRAMEWORK_TOOL_H_

#include <QObject>

class WorkspaceController;

class Tool : public QObject {
	Q_OBJECT

 public:
	 explicit Tool(QObject* parent = nullptr);

	 void setWorkspaceController(WorkspaceController* controller);

	 bool start();;

	 virtual bool OnStart();

private:
	bool m_isActive;
	WorkspaceController* m_workspaceController;
};

#endif  // SRC_IACT_FRAMEWORK_TOOL_H_
