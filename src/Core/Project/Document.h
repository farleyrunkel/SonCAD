// Copyright [2024] SunCAD

#ifndef _Document_H_
#define _Document_H_

#include <TDocStd_Document.hxx>

#include "Core/Project/Workspace.h"

class LayerCollection;

class Document
{
public:
	Document();

	std::vector<std::shared_ptr<Workspace>>& workspaces();

	std::shared_ptr<LayerCollection> layers() const;

private:
	Handle(TDocStd_Document) m_document;

	std::vector<std::shared_ptr<Workspace>> m_workspaces;
	std::shared_ptr<LayerCollection> m_layers;
};

#endif  // _Document_H_
