// Copyright [2024] SunCAD

#ifndef _PropertySignal_H_
#define _PropertySignal_H_

#include <string>

#include <boost/signals2.hpp>

class enable_property_changed_signal
{
public:
	using PropertyChangedSignal = boost::signals2::signal<void(const std::string&)>;

public:
	enable_property_changed_signal();

	PropertyChangedSignal& propertyChanged() { return m_propertyChanged; }

	boost::signals2::connection connectSignal(const PropertyChangedSignal::slot_type& slot)
	{
		return m_propertyChanged.connect(slot);
	}

	bool suppressed() const { return m_suppressed; }
	void setSuppressed(bool suppressed)
	{
		m_suppressed = suppressed;
	}

protected:
	void raisePropertyChanged(const std::string& property)
	{
		if(!m_suppressed && !m_propertyChanged.empty())
		{
			m_propertyChanged(property);
		}
	}

private:
	PropertyChangedSignal m_propertyChanged;
	bool m_suppressed;
};

#endif  // _PropertySignal_H_
