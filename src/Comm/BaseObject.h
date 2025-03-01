// Copyright [2024] SunCAD

#ifndef _BaseObject_H_
#define _BaseObject_H_

#include <boost/signals2.hpp>

#include <Standard_Transient.hxx>
#include <TCollection_AsciiString.hxx>

DEFINE_STANDARD_HANDLE(BaseObject, Standard_Transient)

class BaseObject : public Standard_Transient
{
	using PropertyChangedEventHandler = boost::signals2::signal<void(BaseObject* sender, const TCollection_AsciiString&)>;

public:
	BaseObject() : Standard_Transient(), SuppressPropertyChangedEvent(false) {}

	virtual ~BaseObject()
	{
		PropertyChanged.disconnect_all_slots();
	}

protected: 
	virtual void RaisePropertyChanged(const TCollection_AsciiString& theProperty)
	{
		if (!SuppressPropertyChangedEvent && PropertyChanged.num_slots() > 0)
		PropertyChanged(this, theProperty);
	}

public:
	bool SuppressPropertyChangedEvent;
	PropertyChangedEventHandler PropertyChanged;
};

#endif  // _BaseObject_H_
