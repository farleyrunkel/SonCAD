#ifndef CORE_FRAMEWORK_MESSAGE_PROCESSINGSCOPE_H_
#define CORE_FRAMEWORK_MESSAGE_PROCESSINGSCOPE_H_

#include <functional>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <string>

#include "Core/Topology/Entity.h"
#include "Core/Framework/Message/Messages.h"
#include "Core/Framework/Message/MessageManager.h"

// Processing scope management class
class ProcessingScope
{
public:
    ProcessingScope(std::shared_ptr<Entity> entity, const std::string& desc)
        : entity_(entity), handler_(Messages::getHandler())
    {
        if(handler_)
        {
            handler_->onProcessingStarted(entity, desc);
            // Log the start of processing
            std::cout << "Processing started: " << desc << std::endl;
        }
    }

    ~ProcessingScope()
    {
        if(handler_)
        {
            handler_->onProcessingStopped();
            // Log the end of processing
            std::cout << "Processing stopped" << std::endl;
        }
    }

    template<typename F>
    static bool executeWithGuards(std::shared_ptr<Entity> entity, const std::string& desc, F&& func)
    {
        try
        {
            ProcessingScope scope(entity, desc);
            return func();
        }
        catch(const std::exception& e)
        {
            // Enhanced error logging with exception details
            std::string errorMsg = "Exception in " + desc + ": " + e.what();
            Messages::error(errorMsg, e, entity);
            return false;
        }
    }

private:
    std::shared_ptr<Entity> entity_;
    std::shared_ptr<MessageManager> handler_;
};

#endif  // CORE_FRAMEWORK_MESSAGE_PROCESSINGSCOPE_H_