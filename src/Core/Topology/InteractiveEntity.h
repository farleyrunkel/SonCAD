// Copyright [2024] SunCAD

#ifndef _InteractiveEntity_H_
#define _InteractiveEntity_H_

#include <boost/signals2.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <Standard_Transient.hxx>
#include <TCollection_AsciiString.hxx>

#include "Core/Project/Document.h"
#include "Core/Topology/Entity.h"


DEFINE_STANDARD_HANDLE(InteractiveEntity, Entity)

class InteractiveEntity : public Entity
{
public:
    explicit InteractiveEntity() {}

public:
    virtual TCollection_AsciiString GetName() const
    {
        return myName;
    }


private:
    boost::uuids::uuid myLayerId;

    TCollection_AsciiString myName;
    bool myIsVisible;
};

#endif  // _InteractiveEntity_H_
