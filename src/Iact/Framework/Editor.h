// Copyright [2024] SonCAD

#ifndef SRC_IACT_FRAMEWORK_EDITOR_H_
#define SRC_IACT_FRAMEWORK_EDITOR_H_

#include <QObject>

class Editor : public QObject {
	Q_OBJECT

 public:
	explicit Editor(QObject* parent = nullptr);

	void stopTool();;
};

#endif  // SRC_IACT_FRAMEWORK_EDITOR_H_
