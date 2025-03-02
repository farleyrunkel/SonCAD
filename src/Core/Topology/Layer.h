// Copyright [2024] SunCAD

#ifndef _Layer_H_
#define _Layer_H_

#include <boost/signals2.hpp>

#include <Quantity_Color.hxx>
#include <Standard_Transient.hxx>
#include <TCollection_AsciiString.hxx>

#include "Core/Project/Document.h"
#include "Core/Project/VisualStyles.h"
#include "Core/Topology/Entity.h"

class LayerCollection;

DEFINE_STANDARD_HANDLE(Layer, Entity)

class Layer : public Entity
{
public:
    explicit Layer() {}

public:
    virtual TCollection_AsciiString GetName() const
    {
        return myName;
    }

private:
    TCollection_AsciiString myName;
    bool myIsVisible;
    bool myIsLocked;

    PresentationMode PresentationMode;

    Quantity_Color myColor;
    float Transparency;
    LineStyle LineStyle;
	LineThickness LineThickness;

	Handle(LayerCollection) myLayerCollection;
};

#endif  // _Layer_H_
