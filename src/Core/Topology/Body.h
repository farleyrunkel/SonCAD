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
        return m_Name;
    }

private:
    std::string m_Name;

};

#endif  // _Body_H_
