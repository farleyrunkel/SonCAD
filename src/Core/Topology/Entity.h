// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_ENTITY_H_
#define CORE_TOPOLOGY_ENTITY_H_

#include <boost/signals2.hpp>

#include <Standard_Transient.hxx>
#include <TCollection_AsciiString.hxx>

#include "Core/Project/Document.h"
#include "Comm/Signal.h"

DEFINE_STANDARD_HANDLE(Entity, Standard_Transient)

class Entity : public Standard_Transient
{
public:
    explicit Entity() {}

public:
    PropertyChangedSignal& PropertyChanged()
    {
        return myPropertyChanged;
    }

private:
    Handle(Document) myDocument;
    PropertyChangedSignal myPropertyChanged;
};

#endif  // CORE_TOPOLOGY_ENTITY_H_
