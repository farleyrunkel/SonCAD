#ifndef IUNDOABLETOPOLOGY_H
#define IUNDOABLETOPOLOGY_H

#include <QUuid> 
#include "Core/Topology/Entity.h" 

class IUndoableTopology
{
public:
    virtual ~IUndoableTopology() = default;

    virtual QUuid Guid() const = 0;

    virtual Sun_Entity* FindInstance(const QUuid& instanceGuid) = 0;

    virtual Sun_Entity* GetParent(Sun_Entity* instance) = 0;

    virtual void AddChildFromUndo(Sun_Entity* instance, Sun_Entity* parent) = 0;

    virtual void RemoveChildFromUndo(Sun_Entity* instance) = 0;

    virtual void MoveChildFromUndo(Sun_Entity* instance, Sun_Entity* newParent) = 0;
};

#endif 
