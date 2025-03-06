#ifndef OVERWRITABLE_PARAMETER_SET_H
#define OVERWRITABLE_PARAMETER_SET_H

#include <map>
#include <string>
#include <memory>
#include <functional>
#include <typeindex>

#include <any>
#include <boost/signals2.hpp>

class OverridableParameterSet
{
public:
    using ParameterChangedSignal = boost::signals2::signal<void(const std::string&)>;

    OverridableParameterSet() = default;
    virtual ~OverridableParameterSet() = default;

    // 检查是否有覆盖值
    bool hasOverrides() const { return !overrides_.empty(); }

    // 获取参数值（优先覆盖值，否则默认值）
    template<typename T>
    T get(const std::string& key) const
    {
        auto it = overrides_.find(key);
        if(it != overrides_.end())
        {
            return std::any_cast<T>(it->second);
        }
        it = defaults_.find(key);
        if(it != defaults_.end())
        {
            return std::any_cast<T>(it->second);
        }
        return T{}; // 默认值
    }

    // 设置默认值
    template<typename T>
    void setDefault(const std::string& key, const T& value)
    {
        defaults_[key] = value;
    }

    // 设置覆盖值并触发事件
    template<typename T>
    void set(const std::string& key, const T& value)
    {
        overrides_[key] = value;
        parameterChanged_(key);
    }

    // 重置覆盖值
    void reset(const std::string& key)
    {
        overrides_.erase(key);
        parameterChanged_(key);
    }

    // 订阅参数变更事件
    boost::signals2::connection onParameterChanged(const std::function<void(const std::string&)>& callback)
    {
        return parameterChanged_.connect(callback);
    }

private:
    std::map<std::string, std::any> defaults_;  // 默认值
    std::map<std::string, std::any> overrides_; // 覆盖值
    ParameterChangedSignal parameterChanged_;     // 变更信号
};

class ParameterSets
{
public:
    ParameterSets() = default;
    virtual ~ParameterSets() = default;

    // 获取或创建参数集
    template<typename T>
    std::shared_ptr<T> get()
    {
        static_assert(std::is_base_of<OverridableParameterSet, T>::value,
                      "T must derive from OverridableParameterSet");

        auto typeIdx = std::type_index(typeid(T));
        auto it = sets_.find(typeIdx);
        if(it != sets_.end())
        {
            return std::dynamic_pointer_cast<T>(it->second);
        }

        auto newSet = std::make_shared<T>();
        sets_[typeIdx] = newSet;
        return newSet;
    }

    template<typename T>
    void add(const std::shared_ptr<T>& set)
    {
        static_assert(std::is_base_of<OverridableParameterSet, T>::value,
                      "T must derive from OverridableParameterSet");
        sets_[std::type_index(typeid(*set))] = set;
    }

private:
    std::map<std::type_index, std::shared_ptr<OverridableParameterSet>> sets_;
};

#endif // OVERWRITABLE_PARAMETER_SET_H
