// Copyright [2024] SunCAD

#ifndef _LayerCollection_H_
#define _LayerCollection_H_

#include <vector>
#include <memory>
#include <string>

#include <boost/signals2.hpp>

#include "Core/Project/Document.h"
#include "Core/Topology/Layer.h"

class LayerCollection : public Entity
{
public:
    explicit LayerCollection() {}

private:
	std::vector<std::shared_ptr<Layer>> m_Layers;
	bool m_IsolateActiveLayer;
	std::shared_ptr<Layer> m_ActiveLayer;
	std::shared_ptr<Document> m_Model;

	std::string m_Name;
};

#endif  // _LayerCollection_H_
