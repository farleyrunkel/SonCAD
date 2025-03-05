#ifndef CORE_FRAMEWORK_MESSAGE_MESSAGEHANDLER_H_
#define CORE_FRAMEWORK_MESSAGE_MESSAGEHANDLER_H_

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

#include "Core/Framework/Message/MessageItem.h"

class MessageManager
{
public:
    using MessageSignal = boost::signals2::signal<void(const std::shared_ptr<MessageItem>&)>;
    using ProgressSignal = boost::signals2::signal<void(const std::string&, bool)>; // desc, isStarted

    MessageManager() : logFile_("logs/app_log.txt", std::ios::app)
    {
        if(!logFile_.is_open())
        {
            std::cerr << "Failed to open log file\n";
        }
    }

    ~MessageManager()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        logFile_.close();
    }

    void addMessage(const std::shared_ptr<MessageItem>& item)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        messages_.push_back(item);
        if(auto sender = item->getSender().lock())
        {
            entityMessages_[sender].push_back(item);
        }
        messageThrown_(item);
        logToFile(*item);
    }

    void clearEntityMessages(const std::shared_ptr<Entity>& entity)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = entityMessages_.find(entity);
        if(it != entityMessages_.end())
        {
            it->second.clear(); // 清空与该实体相关的消息
            messages_.erase(std::remove_if(messages_.begin(), messages_.end(),
                            [entity](const std::shared_ptr<MessageItem>& msg) {
                if(auto sender = msg->getSender().lock())
                {
                    return sender == entity;
                }
                return false;
            }), messages_.end());
            entityMessages_.erase(it);
        }
    }

    void onProcessingStarted(std::shared_ptr<Entity> entity, const std::string& desc)
    {
        processingStack_.push_back(entity);
        if(processingStack_.size() == 1)
        {
            progressChanged_(desc, true);
        }
        addMessage(std::make_shared<MessageItem>(MessageSeverity::Info, "Processing started: " + desc, "", entity));
    }

    void onProcessingStopped()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if(!processingStack_.empty())
        {
            auto entity = processingStack_.back();
            processingStack_.pop_back();
            if(processingStack_.empty())
            {
                progressChanged_("", false);
            }
            addMessage(std::make_shared<MessageItem>(MessageSeverity::Info, "Processing stopped", "", entity));
        }
    }

    MessageSignal& onMessageThrown() { return messageThrown_; }
    ProgressSignal& onProgressChanged() { return progressChanged_; }

private:
    std::vector<std::shared_ptr<MessageItem>> messages_;
    std::unordered_map<std::shared_ptr<Entity>, std::vector<std::shared_ptr<MessageItem>>> entityMessages_;
    std::vector<std::shared_ptr<Entity>> processingStack_;
    MessageSignal messageThrown_;
    ProgressSignal progressChanged_;
    std::mutex mutex_;
    std::ofstream logFile_;

    void logToFile(const MessageItem& item)
    {
        if(logFile_.is_open())
        {
            auto now = std::chrono::system_clock::to_time_t(item.getTimestamp());
            std::string timeStr = std::ctime(&now);
            timeStr.pop_back(); // 移除换行符
            logFile_ << "[" << timeStr << "] " << item.toString() << "\n";
            logFile_.flush();
        }
    }
};

#endif  // CORE_FRAMEWORK_MESSAGE_MESSAGEHANDLER_H_
