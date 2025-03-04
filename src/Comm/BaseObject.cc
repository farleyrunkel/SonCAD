// Copyright [2024] SunCAD

// Own include
#include "Comm/BaseObject.h"

#include <string>

#include <boost/signals2.hpp>

enable_property_changed_signal::enable_property_changed_signal()
	: m_suppressed(false)
{}

