// Copyright [2024] SunCAD

#ifndef COMM_BASEOBJECT_H_
#define COMM_BASEOBJECT_H_

#include <string>
#include <boost/signals2.hpp>

#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>

class BaseObject : public Standard_Transient
{
public:
    BaseObject();
    virtual ~BaseObject() override;

    void Dispose();

    // 启用/禁用属性变更事件
    void SuppressPropertyChanged(bool suppress);

    // PropertyChanged 信号
    boost::signals2::signal<void(const std::string&)> PropertyChanged;

protected:
    void RaisePropertyChanged(const std::string& property);

private:
    bool m_suppressPropertyChanged;
};

#endif  // COMM_BASEOBJECT_H_
