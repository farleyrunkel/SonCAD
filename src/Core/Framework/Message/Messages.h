#ifndef OCCT_OCCTHELPER_MESSAGES_H_
#define OCCT_OCCTHELPER_MESSAGES_H_

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "Core/Framework/Message/MessageItem.h"
#include "Core/Framework/Message/MessageManager.h"

// 静态消息发送接口
class Messages
{
public:
    static void warning(const std::string& text, const std::string& explanation = "",
                        std::shared_ptr<Entity> sender = nullptr)
    {
        if(auto handler = getHandler())
        {
            auto message = std::make_shared<MessageItem>(MessageSeverity::Warning, text, explanation, sender);
            handler->addMessage(message);
        }
    }

    static void error(const std::string& text, const std::exception& ex,
                      std::shared_ptr<Entity> sender = nullptr)
    {
        std::string expl = "Exception: " + std::string(ex.what());
        if(auto handler = getHandler())
        {
            auto message = std::make_shared<MessageItem>(MessageSeverity::Error, text, expl, sender);
            handler->addMessage(message);
        }
    }

    static std::shared_ptr<MessageManager> getHandler()
    {
        static std::shared_ptr<MessageManager> handler = std::make_shared<MessageManager>();
        return handler;
    }
};

#endif // OCCT_OCCTHELPER_MESSAGES_H_