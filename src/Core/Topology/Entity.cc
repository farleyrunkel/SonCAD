// Copyright [2024] SunCAD

// Own include
#include "Core/Topology/Entity.h"

// Qt includes
#include <QUuid>
#include <QMetaType>

// Project includes
#include "Core/Topology/Document.h"


// Constructor
Sun_Entity::Sun_Entity() : _Guid(QUuid::createUuid()), _HasErrors(false) 
{
}

// Guid property (using QUuid)
QUuid Sun_Entity::Guid() const 
{
     return _Guid;
}

void Sun_Entity::SetGuid(const QUuid& value)
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
QString Sun_Entity::TypeName() const 
{
    return QString(metaObject()->className());
}

// Name property, virtual
QString Sun_Entity::Name() const
{
    return "Unknown";
}

void Sun_Entity::SetName(const QString&) 
{
}

// Error handling
bool Sun_Entity::HasErrors() const 
{
    return _HasErrors;
}

void Sun_Entity::SetHasErrors(bool HasErrors) 
{
    if (_HasErrors != HasErrors) {
        _HasErrors = HasErrors;
        emit HasErrorsChanged(HasErrors);
        emit ErrorStateChanged(this);
    }
}

// Error handling

Sun_IDocument* Sun_Entity::Sun_Document() const 
{
    return _Document;
}

void Sun_Entity::SetDocument(Sun_IDocument* value)
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
void Sun_Entity::Remove() 
{
}

QString Sun_Entity::ToString() const 
{
    return Name();
}

void Sun_Entity::SaveUndo() {}
