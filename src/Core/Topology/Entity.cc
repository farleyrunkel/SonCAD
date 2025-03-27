// Copyright [2024] SunCAD

#include "Core/Topology/Entity.h"

boost::signals2::signal<void(const Handle(Entity)&)> Entity::EntityRemoved;
boost::signals2::signal<void(const Handle(Entity)&)> Entity::ErrorStateChanged;

// Constructor

Entity::Entity() {}
