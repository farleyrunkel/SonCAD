// Copyright [2024] SunCAD

// Own include
#include "Core/Topology/Entity.h"

// Qt includes
#include <QUuid>
#include <QMetaType>

// Project includes
#include "Core/Topology/Document.h"


// Constructor
Entity::Entity() : _Guid(QUuid::createUuid()), _HasErrors(false) 
{
}

// Guid property (using QUuid)
QUuid Entity::Guid() const 
{
     return _Guid;
}

void Entity::SetGuid(const QUuid& value)
{
    if (_Document) {
        _Document->UnregisterInstance(this);
    }
    _Guid = value;
    if (_Document) {
        _Document->RegisterInstance(this);
    }
}

// Type name property
QString Entity::TypeName() const 
{
    return QString(metaObject()->className());
}

// Name property, virtual
QString Entity::Name() const
{
    return "Unknown";
}

void Entity::SetName(const QString&) 
{
}

// Error handling
bool Entity::HasErrors() const 
{
    return _HasErrors;
}

void Entity::SetHasErrors(bool HasErrors) 
{
    if (_HasErrors != HasErrors) {
        _HasErrors = HasErrors;
        emit HasErrorsChanged(HasErrors);
        emit ErrorStateChanged();
    }
}

// Error handling

IDocument* Entity::Document() const 
{
    return _Document;
}

void Entity::SetDocument(IDocument* value)
{
    if (_Document) {
        _Document->UnregisterInstance(this);
    }
    _Document = value;
    if (_Document) {
        _Document->RegisterInstance(this);
    }
}

// Remove entity
void Entity::Remove() 
{
}

QString Entity::ToString() const 
{
    return Name();
}

void Entity::SaveUndo() {}
