// Copyright [2024] SunCAD

#ifndef _Layer_H_
#define _Layer_H_

#include <boost/signals2.hpp>

#include "Comm/Color.h"

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
        return m_Name;
    }

private:
    std::string m_Name;
    bool m_IsVisible;
    bool m_IsLocked;

    PresentationMode PresentationMode;

    Color m_Color;
    float Transparency;
    LineStyle LineStyle;
	LineThickness LineThickness;

	std::shared_ptr<LayerCollection> m_LayerCollection;
};

#endif  // _Layer_H_
