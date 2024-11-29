// Copyright [2024] SunCAD

#include "Core/EntityContainer.h"

#include "Core/Topology/Entity.h"

EntityContainer::EntityContainer() : Sun_Entity() 
{
    // Initialize the entity list
    entityList = QList<Sun_Entity*>();
}

// Get entity count

int EntityContainer::entityCount() const 
{
    return entityList.size();
}

// Add entity to the container

void EntityContainer::add(Sun_Entity* entity, bool update) 
{
    entityList.append(entity);
    if (update) {
        // Emit signal that an item has been added
        emit collectionChanged(NotifyCollectionChangedAction::Add, entity, entityList.size() - 1);
    }
}

// Remove entity from the container

void EntityContainer::Remove(Sun_Entity* entity, bool update) 
{
    int index = entityList.indexOf(entity);
    if (index < 0) return;

    entityList.removeAt(index);
    entity->Remove(); // Assuming T has its own remove method
    if (update) {
        // Emit signal that an item has been removed
        emit collectionChanged(NotifyCollectionChangedAction::Remove, entity, index);
    }
}

// Get entity at a specific index

Sun_Entity* EntityContainer::get(int index) const 
{
    return entityList.value(index);
}

// Get the index of a specific entity

int EntityContainer::indexOf(Sun_Entity* entity) const 
{
    return entityList.indexOf(entity);
}

// Remove all entities from the container

void EntityContainer::Remove() 
{
    std::for_each(entityList.begin(), entityList.end(), [](Sun_Entity* e) { e->Remove(); });
    entityList.clear();
    Sun_Entity::Remove();  // Call the base class remove
}
