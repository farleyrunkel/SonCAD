// Copyright [2024] SunCAD

#ifndef _BaseObject_H_
#define _BaseObject_H_

#include <string>

#include <boost/signals2.hpp>

class enable_property_changed_signal
{
public:
	using PropertyChangedSignal = boost::signals2::signal<void(const std::string&)>;

public:
	enable_property_changed_signal();

	virtual ~enable_property_changed_signal();

	PropertyChangedSignal& PropertyChanged() { return myPropertyChanged; }

protected: 
	virtual void RaisePropertyChanged(const std::string& theProperty);

private:
	bool mySuppressPropertyChangedEvent;
	PropertyChangedSignal myPropertyChanged;
};


#endif  // _BaseObject_H_
