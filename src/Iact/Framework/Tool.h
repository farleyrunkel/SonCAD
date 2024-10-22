// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_TOOL_H_
#define SRC_IACT_FRAMEWORK_TOOL_H_

#include <QObject>

class Tool : public QObject {
	Q_OBJECT

 public:
	 explicit Tool(QObject* parent = nullptr);

	 bool start() { return false; }
};

#endif  // SRC_IACT_FRAMEWORK_TOOL_H_
