// Copyright [2024] SunCAD

// Own include
#include "Comm/BaseObject.h"

#include <string>

#include <boost/signals2.hpp>

enable_property_changed_signal::enable_property_changed_signal()
	: mySuppressPropertyChangedEvent(false)
{}

enable_property_changed_signal::~enable_property_changed_signal()
{
	myPropertyChanged.disconnect_all_slots();
}

void enable_property_changed_signal::RaisePropertyChanged(const std::string& theProperty)
{
	if(!mySuppressPropertyChangedEvent && myPropertyChanged.num_slots() > 0)
		myPropertyChanged(theProperty);
}
