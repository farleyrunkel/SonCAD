// Copyright [2024] SunCAD

#ifndef _Body_H_
#define _Body_H_

#include <string>

#include "Core/Project/Document.h"
#include "Core/Topology/InteractiveEntity.h"


class Body : public InteractiveEntity
{
public:
    explicit Body() {}

public:
    virtual std::string GetName() const
    {
        return myName;
    }

private:
    std::string myName;

};

#endif  // _Body_H_
