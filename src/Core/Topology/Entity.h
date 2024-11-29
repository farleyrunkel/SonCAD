// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_ENTITY_H_
#define SRC_CORE_TOPOLOGY_ENTITY_H_

#include <QObject>
#include <QUuid>
#include <QDebug>

#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>

#include "Comm/BaseObject.h"

class Sun_IDocument;

DEFINE_STANDARD_HANDLE(Sun_Entity, Standard_Transient);

// Base class for Entity, assuming Entity is derived from QObject for signal/slot support
class Sun_Entity : public Sun_BaseObject
{
    Q_OBJECT
    Q_PROPERTY(QUuid Uuid READ Guid WRITE SetGuid NOTIFY GuidChanged)
    Q_PROPERTY(bool HasErrors READ HasErrors WRITE SetHasErrors NOTIFY HasErrorsChanged)
    Q_PROPERTY(QString Name READ Name WRITE SetName)
    Q_PROPERTY(QString TypeName READ TypeName)
    Q_PROPERTY(Sun_IDocument* Sun_Document READ Sun_Document WRITE SetDocument)

public:
    // Constructor
    Sun_Entity();

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
    Sun_IDocument* Sun_Document() const;

    void SetDocument(Sun_IDocument* HasErrors);

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
    void ErrorStateChanged(const Handle(Sun_Entity)&);
    // Signal when the entity is removed
    void EntityRemoved(const Handle(Sun_Entity)&);

 protected:
    QUuid _Guid;
    bool _HasErrors;
    Sun_IDocument* _Document;
};

#endif  // SRC_CORE_TOPOLOGY_ENTITY_H_
