#ifndef MessageItem_H_
#define MessageItem_H_

#include <chrono>
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <boost/signals2.hpp>

#include "Core/Topology/Entity.h"

// 消息严重性枚举
enum class MessageSeverity
{
    Trace,
    Info,
    Warning,
    Error
};

// 消息实体类
class MessageItem
{
public:
    MessageItem(MessageSeverity severity, std::string text,
                std::string explanation = "", std::weak_ptr<Entity> sender = {})
        : timestamp_(std::chrono::system_clock::now()),
        severity_(severity),
        text_(std::move(text)),
        explanation_(splitExplanation(explanation)),
        sender_(sender)
    {}

    std::string toString() const
    {
        std::string result = severityToString(severity_) + ": " + text_;
        if(auto sender = sender_.lock())
        {
            result += " [" + sender->GetName() + "]";
        }
        for(const auto& line : explanation_)
        {
            result += "\n" + line;
        }
        return result;
    }

    MessageSeverity getSeverity() const { return severity_; }
    std::weak_ptr<Entity> getSender() const { return sender_; }
    auto getTimestamp() const { return timestamp_; }

private:
    std::chrono::system_clock::time_point timestamp_;
    MessageSeverity severity_;
    std::string text_;
    std::vector<std::string> explanation_;
    std::weak_ptr<Entity> sender_;

    static std::vector<std::string> splitExplanation(const std::string& exp)
    {
        std::vector<std::string> result;
        size_t start = 0, end;
        while((end = exp.find_first_of("\n\r", start)) != std::string::npos)
        {
            if(end > start) result.emplace_back(exp.substr(start, end - start));
            start = end + 1;
        }
        if(start < exp.length()) result.emplace_back(exp.substr(start));
        return result;
    }

    static std::string severityToString(MessageSeverity s)
    {
        switch(s)
        {
        case MessageSeverity::Trace: return "Trace";
        case MessageSeverity::Info: return "Info";
        case MessageSeverity::Warning: return "Warning";
        case MessageSeverity::Error: return "Error";
        default: return "Unknown";
        }
    }
};

#endif // !MessageItem_H_
