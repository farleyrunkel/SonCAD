// Copyright [2024] SunCAD

#include "Core/Topology/Model.h"

Model::Model() {
}

QVector<Sun::Sun_Workspace*>& Model::workspaces() {
	return m_workspaces; 
}
