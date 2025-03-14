// Copyright [2024] SunCAD

#ifndef COMM_BASEOBJECT_H_
#define COMM_BASEOBJECT_H_

#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>
#include <boost/signals2.hpp>
#include <string>

class BaseObject : public Standard_Transient
{
public:
    BaseObject();
    virtual ~BaseObject() override;

    void Dispose();

    // PropertyChanged 信号
    boost::signals2::signal<void(const std::string&)> PropertyChanged;

    // 启用/禁用属性变更事件
    void SuppressPropertyChanged(bool suppress);

protected:
    void RaisePropertyChanged(const std::string& property);

private:
    bool m_suppressPropertyChanged;
};

#endif  // COMM_BASEOBJECT_H_
