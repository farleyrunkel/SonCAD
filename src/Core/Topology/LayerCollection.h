// Copyright [2024] SunCAD

#ifndef _LayerCollection_H_
#define _LayerCollection_H_

#include <boost/signals2.hpp>

#include <NCollection_Vector.hxx>
#include <TCollection_AsciiString.hxx>

#include "Core/Project/Document.h"
#include "Core/Topology/Layer.h"

DEFINE_STANDARD_HANDLE(LayerCollection, Entity)

class LayerCollection : public Entity
{
public:
    explicit LayerCollection() {}

private:
	NCollection_Vector<Handle(Layer)> myLayers;
	bool myIsolateActiveLayer;
	Handle(Layer) myActiveLayer;
	Handle(Document) myModel;

	TCollection_AsciiString myName;
};

#endif  // _LayerCollection_H_
