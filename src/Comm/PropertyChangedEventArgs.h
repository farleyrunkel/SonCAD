// Copyright [2024] SunCAD

#ifndef COMM_PROPERTYCHANGEDEVENTARGS_H_
#define COMM_PROPERTYCHANGEDEVENTARGS_H_

#include <string>
#include <any>

#include <Standard_Handle.hxx>


class enable_property_changed_signal;

class PropertyChangedEventArgs {
public:
    PropertyChangedEventArgs(const std::string& propertyName = "", enable_property_changed_signal* sender = nullptr)
        : _PropertyName(propertyName), _Object(sender) {}

    enable_property_changed_signal* Sender() const {
        return _Object;
    }

    // ทรฮส propertyName
    const std::string& PropertyName() const {
        return _PropertyName;
    }

private:
    enable_property_changed_signal* _Object;
    std::string _PropertyName;
};



#endif  // COMM_PROPERTYCHANGEDEVENTARGS_H_
