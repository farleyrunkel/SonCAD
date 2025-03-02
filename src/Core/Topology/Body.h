// Copyright [2024] SunCAD

#ifndef _Body_H_
#define _Body_H_

#include <Standard_Transient.hxx>
#include <TCollection_AsciiString.hxx>

#include "Core/Project/Document.h"
#include "Core/Topology/InteractiveEntity.h"

DEFINE_STANDARD_HANDLE(Body, InteractiveEntity)

class Body : public InteractiveEntity
{
public:
    explicit Body() {}

public:
    virtual TCollection_AsciiString GetName() const
    {
        return myName;
    }

private:
    TCollection_AsciiString myName;

};

#endif  // _Body_H_
