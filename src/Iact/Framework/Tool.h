// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_TOOL_H_
#define SRC_IACT_FRAMEWORK_TOOL_H_

#include <QObject>

#include "Iact/Framework/WorkspaceControl.h"

class Tool : public WorkspaceControl {
	Q_OBJECT

 public:
	 explicit Tool(QObject* parent = nullptr);

	 bool start();;

	 virtual bool OnStart();

 private:
	bool m_isActive;
};

#endif  // SRC_IACT_FRAMEWORK_TOOL_H_
