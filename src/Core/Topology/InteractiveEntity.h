// Copyright [2024] SunCAD

#ifndef _InteractiveEntity_H_
#define _InteractiveEntity_H_

#include <boost/signals2.hpp>
#include <boost/uuid/uuid.hpp>

 
#include <TCollection_AsciiString.hxx>

#include "Core/Project/Document.h"
#include "Core/Topology/Entity.h"

class InteractiveEntity : public Entity
{
public:
    explicit InteractiveEntity() {}

public:
    virtual std::string GetName() const
    {
        return m_Name;
    }

private:
    boost::uuids::uuid m_LayerId;

    std::string m_Name;
    bool m_IsVisible;
};

#endif  // _InteractiveEntity_H_
