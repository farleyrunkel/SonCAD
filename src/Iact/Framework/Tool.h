// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_TOOL_H_
#define SRC_IACT_FRAMEWORK_TOOL_H_

#include <QObject>
#include <QString>

#include "Iact/Framework/WorkspaceControl.h"
#include "Iact/Framework/ToolAction.h"

class Tool : public WorkspaceControl {
	Q_OBJECT

 public:
	explicit Tool(QObject* parent = nullptr);

 public:
	bool start();

	virtual bool onStart();

	ToolAction* currentAction() const;

	bool cancel(bool force);

	void stop();

	virtual bool prepareUndo();

 protected:
	virtual bool onCancel();

	virtual void onStop();


	virtual void cleanup();

	//void BaseCleanup() {
	//	CleanedUp = true;
	//}

	bool startAction(ToolAction* toolAction, bool exclusive = true);

	void stopAction(ToolAction* toolAction);

	void stopAllActions();

 signals:
	void toolActionChanged(ToolAction*);

 private:
	QVector<ToolAction*> m_toolActions;
	QString id;
	bool m_isActive;
};

#endif  // SRC_IACT_FRAMEWORK_TOOL_H_
