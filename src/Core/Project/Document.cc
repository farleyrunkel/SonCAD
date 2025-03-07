// Copyright [2024] SunCAD

#include "Core/Project/Document.h"

#include <memory>
#include <vector>

#include "Core/Project/Workspace.h"
#include "Core/Topology/LayerCollection.h"

Document::Document()
{}

std::vector<std::shared_ptr<Workspace>>& Document::workspaces()
{
	return m_workspaces;
}

std::shared_ptr<LayerCollection> Document::layers() const
{
	return m_layers;
}
