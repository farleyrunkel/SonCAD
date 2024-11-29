// Copyright [2024] SunCAD

#ifndef SRC_CORE_ENTITYCONTAINER_H_
#define SRC_CORE_ENTITYCONTAINER_H_

#include <QObject>
#include <QList>
#include <QVariant>
#include <algorithm>

#include "Core/Topology/Entity.h"

// Enum to mimic NotifyCollectionChangedAction
enum class NotifyCollectionChangedAction 
{
    Add,
    Remove,
    Replace,
    Reset
};

class EntityContainer : public Sun_Entity 
{
    Q_OBJECT

 public:
    EntityContainer();

    // Get entity count
    int entityCount() const;

    // Add entity to the container
    virtual void add(Sun_Entity* entity, bool update = true);

    // Remove entity from the container
    virtual void Remove(Sun_Entity* entity, bool update = true);

    // Get entity at a specific index
    virtual Sun_Entity* get(int index) const;

    // Get the index of a specific entity
    virtual int indexOf(Sun_Entity* entity) const;

    // Remove all entities from the container
    void Remove() override;

 signals:
    // Qt signal for notifying collection changes
    void collectionChanged(NotifyCollectionChangedAction action, Sun_Entity* entity, int index);

 protected:
    // QList to hold the entities
    QList<Sun_Entity*> entityList;
};

#endif  // SRC_CORE_ENTITYCONTAINER_H_
