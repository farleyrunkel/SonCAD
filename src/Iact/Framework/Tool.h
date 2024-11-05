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
	bool start();;

	virtual bool OnStart();

	ToolAction* currentAction() const {
		return m_toolActions.size() > 0 ? m_toolActions.first() : nullptr;
	}

	bool Cancel(bool force) {
		if (!OnCancel() && !force)
			return false;

		if (m_isActive)
			Stop();
		return true;
	}

	void Stop() {
		m_isActive = false;
		OnStop();
		Cleanup();

		workspaceController()->removeTool(this);
		workspaceController()->invalidate();
	}

	virtual bool prepareUndo() {
		return Cancel(false);
	}

 protected:
	virtual bool OnCancel() {
		return true;
	}

	virtual void OnStop() {}


	virtual void Cleanup() {
		//StopAllActions();
		//RestoreAllVisualShapes();
		//BaseCleanup();
	}

	//void BaseCleanup() {
	//	CleanedUp = true;
	//	// 基类清理逻辑可以在此处实现
	//}

	bool startAction(ToolAction* toolAction, bool exclusive = true) {
		if ( !m_toolActions.isEmpty() && std::find(m_toolActions.begin(), m_toolActions.end(), toolAction) != m_toolActions.end())
			return true;

		try {
			if (exclusive) {
				stopAllActions();
			}

			if (toolAction != nullptr) {
				toolAction->setWorkspaceController(workspaceController());
				if (!toolAction->start())
					return false;

				m_toolActions.insert(m_toolActions.begin(), toolAction);
				emit toolActionChanged(toolAction);
			}
			return true;
		}
		catch (const std::exception& e) {
			std::cerr << "Starting tool action failed: " << e.what() << std::endl;
			return false;
		}
	}

	void stopAction(ToolAction* toolAction) {
		if (toolAction == nullptr)
			return;

		if (!m_toolActions.isEmpty())
			m_toolActions.erase(std::remove(m_toolActions.begin(), m_toolActions.end(), toolAction), m_toolActions.end());

		toolAction->stop();
		emit toolActionChanged(toolAction);
	}

	void stopAllActions() {
		for (const auto& action : m_toolActions) {
			stopAction(action);
		}
		m_toolActions.clear();
	}

 signals:
	void toolActionChanged(ToolAction*);

 private:
	QVector<ToolAction*> m_toolActions;
	QString id;
	bool m_isActive;
};

#endif  // SRC_IACT_FRAMEWORK_TOOL_H_
