// Copyright [2024] SunCAD

#ifndef _BaseObject_H_
#define _BaseObject_H_

#include <boost/signals2.hpp>

#include <Standard_Transient.hxx>
#include <TCollection_AsciiString.hxx>

DEFINE_STANDARD_HANDLE(BaseObject, Standard_Transient)

class BaseObject : public Standard_Transient
{
	DEFINE_STANDARD_RTTIEXT(BaseObject, Standard_Transient)

	using PropertyChangedSignal = boost::signals2::signal<void(BaseObject*, const TCollection_AsciiString&)>;

public:
	BaseObject();

	virtual ~BaseObject() override;

protected: 
	virtual void RaisePropertyChanged(const TCollection_AsciiString& theProperty);

public:
	PropertyChangedSignal PropertyChanged;

private:
	bool SuppressPropertyChangedEvent;
};

#endif  // _BaseObject_H_
