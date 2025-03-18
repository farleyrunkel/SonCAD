// Copyright [2024] SunCAD

#ifndef COMM_ParameterSets_H_
#define COMM_ParameterSets_H_

#include <any>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <sstream>

#include <typeindex>
#include <nlohmann/json.hpp>
#include <boost/signals2.hpp>

using json = nlohmann::json;

class OverridableParameterSet
{
public:
    using SignalType = boost::signals2::signal<void(OverridableParameterSet*, const std::string&)>;
    using Connection = boost::signals2::connection;

    bool HasOverriddenParameters() const { return !overriddenValues_.empty(); }

    // 获取值
    template<typename T>
    T GetValue(const std::string& key) const
    {
        if(auto it = overriddenValues_.find(key); it != overriddenValues_.end())
            return std::any_cast<T>(it->second);
        if(auto it = defaultValues_.find(key); it != defaultValues_.end())
            return std::any_cast<T>(it->second);
        return T{};
    }

    // 设置默认值
    template<typename T>
    void SetDefaultValue(const std::string& key, T value)
    {
        defaultValues_[key] = std::move(value);
    }

    // 设置覆盖值
    template<typename T>
    void SetValue(const std::string& key, T value)
    {
        overriddenValues_[key] = std::move(value);
        ParameterChanged(this, key);
    }

    // 重置值
    void ResetValue(const std::string& key)
    {
        overriddenValues_.erase(key);
        ParameterChanged(this, key);
    }

    // 序列化
    void Write(std::ostream& os) const
    {
        json j;
        for(const auto& [key, value] : overriddenValues_)
        {
            if(value.type() == typeid(int)) j[key] = std::any_cast<int>(value);
            else if(value.type() == typeid(bool)) j[key] = std::any_cast<bool>(value);
            else if(value.type() == typeid(double)) j[key] = std::any_cast<double>(value);
            // 可扩展其他类型支持
        }
        os << j.dump();
    }

    // 反序列化
    void Read(std::istream& is)
    {
        json j = json::parse(is);
        for(auto& [key, value] : j.items())
        {
            if(defaultValues_.find(key)!= defaultValues_.end())
            {
                if(value.is_number_integer()) overriddenValues_[key] = value.get<int>();
                else if(value.is_boolean()) overriddenValues_[key] = value.get<bool>();
                else if(value.is_number_float()) overriddenValues_[key] = value.get<double>();
                // 可扩展其他类型支持
            }
        }
    }

public:
    static SignalType ParameterChanged; // Boost信号

protected:
    OverridableParameterSet() = default;

private:
    std::unordered_map<std::string, std::any> overriddenValues_;
    std::unordered_map<std::string, std::any> defaultValues_;
};

// 参数集集合
class ParameterSets
{
public:
    template<typename T>
    T* Get()
    {
        static_assert(std::is_base_of_v<OverridableParameterSet, T>, "T must derive from OverridableParameterSet");
        auto type = std::type_index(typeid(T));
        if(auto it = parameterSets_.find(type); it != parameterSets_.end())
            return static_cast<T*>(it->second.get());

        auto newSet = std::make_unique<T>();
        T* ptr = newSet.get();
        parameterSets_[type] = std::move(newSet);
        return ptr;
    }

    template<typename T>
    void Add(std::unique_ptr<T> set)
    {
        static_assert(std::is_base_of_v<OverridableParameterSet, T>, "T must derive from OverridableParameterSet");
        parameterSets_[std::type_index(typeid(T))] = std::move(set);
    }

    // 序列化
    void Write(std::ostream& os) const
    {
        json j;
        for(const auto& [type, _set] : parameterSets_)
        {
            if(!_set->HasOverriddenParameters()) continue;
            std::ostringstream oss;
            _set->Write(oss);
            j[type.name()] = json::parse(oss.str());
        }
        os << j.dump();
    }

    // 反序列化
    void Read(std::istream& is)
    {
        parameterSets_.clear();
        json j = json::parse(is);
        for(auto& [typeName, value] : j.items())
        {
            // 需工厂模式映射类型名到实例创建，此处略
        }
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<OverridableParameterSet>> parameterSets_;
};
#endif  // COMM_ParameterSets_H_
