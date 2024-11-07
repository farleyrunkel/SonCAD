// Copyright [2024] SunCAD

#include "Core/Topology/Model.h"

Model::Model() {
}

QVector<Workspace*>& Model::workspaces() {
	return m_workspaces; 
}
