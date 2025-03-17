
#ifndef Entity_DOCUMENT_H
#define Entity_DOCUMENT_H
// Copyright [2024] SunCAD

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QUuid>

#include <TDF_Label.hxx>

#include "Comm/BaseObject.h"

DEFINE_STANDARD_HANDLE(Entity, BaseObject)

// Base class for Entity, assuming Entity is derived from QObject for signal/slot support
class Entity : public BaseObject
{

public:
    // Constructor
    explicit Entity();

    explicit Entity(const TDF_Label& label) {}

    // Guid property (using QUuid)
    QUuid Guid() const;

    void SetGuid(const QUuid& Guid);

    // Type name property
    QString TypeName() const;

    // Name property, virtual
    virtual QString GetName() const;

    virtual void SetName(const QString& /*unused*/);

    // Error handling
    bool HasErrors() const;

    void SetHasErrors(bool HasErrors);

    // Remove entity
    virtual void Remove();

    // For debugging or logging purposes
    virtual QString ToString() const;

protected:
    QUuid _Guid;
    bool _HasErrors;
};

#endif  // Entity_DOCUMENT_H
