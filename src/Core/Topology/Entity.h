// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_ENTITY_H_
#define CORE_TOPOLOGY_ENTITY_H_

#include <boost/signals2.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <Standard_Transient.hxx>
#include <TCollection_AsciiString.hxx>

#include "Comm/Signal.h"
#include "Core/Project/Document.h"

DEFINE_STANDARD_HANDLE(Entity, Standard_Transient)

class Entity : public Standard_Transient
{
public:
    explicit Entity() {}

    virtual TCollection_AsciiString GetName() const { return "Unknown"; }

public:
    PropertyChangedSignal& PropertyChanged()
    {
        return myPropertyChanged;
    }

private:
    boost::uuids::uuid myLayerId;

    Handle(Document) myDocument;
    PropertyChangedSignal myPropertyChanged;

};

#endif  // CORE_TOPOLOGY_ENTITY_H_
