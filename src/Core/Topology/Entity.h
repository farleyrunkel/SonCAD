// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_ENTITY_H_
#define SRC_CORE_TOPOLOGY_ENTITY_H_

#include <QObject>
#include <QUuid>
#include <QDebug>

#include <Standard_Transient.hxx>

#include "Comm/BaseObject.h"

class IDocument;

// DEFINE_STANDARD_HANDLE(Entity, Standard_Transient)

// Base class for Entity, assuming Entity is derived from QObject for signal/slot support
class Entity : public BaseObject
{
    Q_OBJECT
    Q_PROPERTY(QUuid Uuid READ Guid WRITE SetGuid NOTIFY GuidChanged)
    Q_PROPERTY(bool HasErrors READ HasErrors WRITE SetHasErrors NOTIFY HasErrorsChanged)
    Q_PROPERTY(QString Name READ Name WRITE SetName)
    Q_PROPERTY(QString TypeName READ TypeName)
    Q_PROPERTY(IDocument* Document READ Document WRITE SetDocument)

public:
    // Constructor
    Entity();

public:
    // Guid property (using QUuid)
    QUuid Guid() const;

    void SetGuid(const QUuid& Guid);

    // Type name property
    QString TypeName() const;

    // Name property, virtual
    virtual QString Name() const;

    virtual void SetName(const QString&);

    // Error handling
    bool HasErrors() const;

    void SetHasErrors(bool HasErrors);
    // Error handling
    IDocument* Document() const;

    void SetDocument(IDocument* HasErrors);

    // Remove entity
    virtual void Remove();

    // For debugging or logging purposes
    virtual QString ToString() const;

    void SaveUndo();;

signals:
    // Signal when hasErrors changes
    void HasErrorsChanged(bool);

    // Signal when the entity's GUID changes
    void GuidChanged(const QUuid&);

    // Signal when the error state changes
    void ErrorStateChanged();
    // Signal when the entity is removed
    void EntityRemoved();

 protected:
    QUuid _Guid;
    bool _HasErrors;
    IDocument* _Document;
};

#endif  // SRC_CORE_TOPOLOGY_ENTITY_H_

