// Copyright [2024] SunCAD

#ifndef SRC_COMM_BASEOBJECT_H_
#define SRC_COMM_BASEOBJECT_H_

#include <QObject>
#include <QString>

class BaseObject : public QObject {
	Q_OBJECT
public:
		BaseObject(QObject* parent = nullptr):QObject(parent){}

signals: 
	void propertyChanged(const QString& property);
};


#endif  // SRC_COMM_BASEOBJECT_H_
