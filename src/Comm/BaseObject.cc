// Copyright [2024] SunCAD

// Own include
#include "Comm/BaseObject.h"

#include <boost/signals2.hpp>

#include <Standard_Transient.hxx>
#include <TCollection_AsciiString.hxx>

IMPLEMENT_STANDARD_RTTIEXT(BaseObject, Standard_Transient)

BaseObject::BaseObject() : Standard_Transient(), SuppressPropertyChangedEvent(false)
{}

BaseObject::~BaseObject()
{
	PropertyChanged.disconnect_all_slots();
}

void BaseObject::RaisePropertyChanged(const TCollection_AsciiString& theProperty)
{
	if(!SuppressPropertyChangedEvent && PropertyChanged.num_slots() > 0)
		PropertyChanged(this, theProperty);
}
