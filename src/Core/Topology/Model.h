// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_MODEL_H_
#define SRC_CORE_TOPOLOGY_MODEL_H_

#include <QObject>
#include <QVector>

#include "Core/Workspace.h"

class Model : public QObject {
	Q_OBJECT

 public:
	Model()  {

	}

	QVector<Workspace*>& workspaces() { return m_workspaces; }

 signals:
	void resetUnsavedChanges();

 private:

	QVector<Workspace*> m_workspaces;
};


#endif  // SRC_CORE_TOPOLOGY_MODEL_H_