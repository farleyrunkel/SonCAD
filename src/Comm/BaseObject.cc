// Copyright [2024] SunCAD

#include "Comm/BaseObject.h"

BaseObject::BaseObject()
    : m_suppressPropertyChanged(false)
{}

BaseObject::~BaseObject()
{}

void BaseObject::Dispose()
{
    // 释放资源或执行清理操作
}

void BaseObject::SuppressPropertyChanged(bool suppress)
{
    m_suppressPropertyChanged = suppress;
}

void BaseObject::RaisePropertyChanged(const std::string& property)
{
    if(!m_suppressPropertyChanged)
    {
        PropertyChanged(property);
    }
}
