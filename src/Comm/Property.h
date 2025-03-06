#ifndef PROPERTY_H
#define PROPERTY_H

#include <boost/signals2.hpp>
#include <functional>
#include <mutex>
#include <utility>
#include <iostream>
#include <type_traits>

// 约束 T 必须是类类型
template<typename T, typename = std::enable_if_t<std::is_class_v<T>>>
class Property : public T
{
public:
    using T::T;
    // 默认构造函数
    Property() = default;

    // 带初始值的构造函数
    Property(const T& value) : T(value) {}

    // 只读属性构造函数
    Property(const T& value, bool readOnly)
        : T(value),
        setter_(readOnly ? nullptr : [this](const T& v) { setValue(v); })
    {}

    // 支持自定义 getter 和 setter 的构造函数
    Property(std::function<T()> getter, std::function<void(const T&)> setter)
        : getter_(std::move(getter)), setter_(std::move(setter))
    {}

    // getter
    T get() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        try
        {
            return getter_ ? getter_() : static_cast<const T&>(*this);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Getter error: " << e.what() << "\n";
            return static_cast<const T&>(*this); // 回退到当前对象
        }
    }

    // setter
    void set(const T& value)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        T oldValue = get();
        if(!setter_ && value != oldValue)
        {
            throw std::runtime_error("Property is read-only");
        }
        if(setter_)
        {
            try
            {
                setter_(value);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Setter error: " << e.what() << "\n";
                return;
            }
        }
        else
        {
            setValue(value);
        }
        if(value != oldValue)
        {
            changed(value); // 发送 changed 信号
        }
    }

    // 运算符重载：模拟 C# 的直接赋值
    Property& operator=(const T& value)
    {
        set(value);
        return *this;
    }

    // 运算符重载：模拟 C# 的直接取值
    operator T&() const
    {
        return get();
    }

public:
    boost::signals2::signal<void(T)> changed; // 属性变更信号

private:
    mutable std::mutex mutex_; // mutable 允许 const 方法加锁
    std::function<T()> getter_{nullptr};
    std::function<void(const T&)> setter_{nullptr};

    // 内部设置值
    void setValue(const T& value)
    {
        static_cast<T&>(*this) = value; // 更新基类内容
    }
};

#endif // PROPERTY_H