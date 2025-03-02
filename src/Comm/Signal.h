// Copyright [2024] SunCAD

#ifndef _Signal_H_
#define _Signal_H_

#include <boost/signals2.hpp>

#include <Standard_Transient.hxx>
#include <TCollection_AsciiString.hxx>

using PropertyChangedSignal = boost::signals2::signal<void(Standard_Transient*, const TCollection_AsciiString&)>;

#endif  // _Signal_H_
