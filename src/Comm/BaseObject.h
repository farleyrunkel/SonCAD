// Copyright [2024] SunCAD

#ifndef SRC_COMM_BASEOBJECT_H_
#define SRC_COMM_BASEOBJECT_H_

#include <QObject>
#include <QString>

#include <Standard_Transient.hxx>

class BaseObject : public QObject, public Standard_Transient
{
	Q_OBJECT

public:
	BaseObject() = default;
};

#endif  // SRC_COMM_BASEOBJECT_H_
