// Copyright [2024] SunCAD

#ifndef COMM_BASEOBJECT_H_
#define COMM_BASEOBJECT_H_

#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>

class BaseObject : public Standard_Transient
{
public:
	BaseObject();

	void Dispose();

	virtual ~BaseObject() override;
};

#endif  // COMM_BASEOBJECT_H_
