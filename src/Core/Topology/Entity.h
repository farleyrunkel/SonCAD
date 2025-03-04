// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_ENTITY_H_
#define CORE_TOPOLOGY_ENTITY_H_

#include <boost/signals2.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

 
#include <TCollection_AsciiString.hxx>

#include "Core/Project/Document.h"

class Entity : public Standard_Transient
{
public:
    explicit Entity() {}

    virtual std::string GetName() const { return "Unknown"; }

public:

private:
    boost::uuids::uuid myLayerId;

    std::shared_ptr<Document> myDocument;
};

#endif  // CORE_TOPOLOGY_ENTITY_H_
