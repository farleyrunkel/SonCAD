// Copyright [2024] SunCAD

#ifndef _Layer_H_
#define _Layer_H_

#include <boost/signals2.hpp>

#include <Quantity_Color.hxx>
 
#include <TCollection_AsciiString.hxx>

#include "Core/Project/Document.h"
#include "Core/Project/VisualStyles.h"
#include "Core/Topology/Entity.h"

class LayerCollection;

class Layer : public Entity
{
public:
    explicit Layer() {}

public:
    virtual std::string GetName() const
    {
        return myName;
    }

private:
    std::string myName;
    bool myIsVisible;
    bool myIsLocked;

    PresentationMode PresentationMode;

    Quantity_Color myColor;
    float Transparency;
    LineStyle LineStyle;
	LineThickness LineThickness;

	std::shared_ptr<LayerCollection> myLayerCollection;
};

#endif  // _Layer_H_
