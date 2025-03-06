#ifndef _CoreContext_h_
#define _CoreContext_h_

#include <memory>
#include <string>

#include <boost/signals2.hpp>

#include "Comm/ParameterSet.h"
#include "Core/Framework/Message/MessageManager.h"
#include "Core/Project/Document.h"
#include "Core/Project/Viewport.h"
#include "Core/Project/Workspace.h"
#include "Core/Topology/LayerCollection.h"

class CoreContext
{
public:
    CoreContext()
    {
        current_ = this;
        MessageManager_ = std::make_unique<MessageManager>();
    }

    CoreContext(const CoreContext&) = delete;
    CoreContext& operator=(const CoreContext&) = delete;

    virtual ~CoreContext()
    {
        dispose(false);
    }

    static CoreContext* current() noexcept
    {
        return current_;
    }

    static void setCurrent(CoreContext* context)
    {
        delete current_; // 手动释放旧实例
        current_ = context;
    }

    // Workspace 属性
    virtual std::shared_ptr<Workspace> workspace() const
    {
        return workspace_;
    }

    virtual void setWorkspace(std::shared_ptr<Workspace> workspace)
    {
        workspace_ = std::move(workspace);
        //setViewport(workspace_ ? workspace_->viewports().front() : nullptr);
        raisePropertyChanged("workspace");
    }

    // Viewport 属性
    virtual std::shared_ptr<Viewport> viewport() const
    {
        return viewport_;
    }

    virtual void setViewport(std::shared_ptr<Viewport> viewport)
    {
        viewport_ = std::move(viewport);
        raisePropertyChanged("viewport");
    }

    // Document 属性
    virtual std::shared_ptr<Document> document() const
    {
        return document_;
    }

    virtual void setDocument(std::shared_ptr<Document> document)
    {
        document_ = std::move(document);

        raisePropertyChanged("document");
        raisePropertyChanged("undoHandler");
        raisePropertyChanged("layers");

        //if(document_ && document_->layers())
        //{
        //    document_->layers()->onActivated();
        //}

        //// 检查 Workspace 是否属于新 Document
        //if(document_ && !document_->workspaces().contains(workspace_))
        //{
        //    setWorkspace(document_->workspaces().empty() ? nullptr : document_->workspaces().front());
        //}
    }

    // Layers 属性（只读）
    virtual LayerCollection* layers() const
    {
        //return document_ ? document_->layers() : nullptr;
    }

    //// MessageManager 属性（只读）
    //MessageManager* MessageManager() const
    //{
    //    return MessageManager_.get();
    //}

    // Parameters 属性
    virtual std::shared_ptr<ParameterSets> parameters()
    {
        if(!parameterSets_)
        {
            parameterSets_ = loadLocalSettings<ParameterSets>("parameters");
            if(!parameterSets_)
            {
                parameterSets_ = std::make_shared<ParameterSets>();
            }
        }
        return parameterSets_;
    }

    // 保存设置
    virtual void saveSettings()
    {
        if(parameterSets_)
        {
            saveLocalSettings("parameters", parameterSets_);
        }
    }

    // 虚函数：保存和加载本地设置
    virtual void saveLocalSettings(const std::string& name, const std::shared_ptr<void>& obj) {}

    template<typename T>
    std::shared_ptr<T> loadLocalSettings(const std::string& name)
    {
        return nullptr;
    }

    // 属性变更信号
    boost::signals2::signal<void(const std::string&)> propertyChanged;

protected:
    virtual void dispose(bool disposing)
    {
        if(disposing)
        {
            //MessageManager_.reset();
        }
        workspace_.reset();
        viewport_.reset();
        document_.reset();
    }

    void raisePropertyChanged(const std::string& propertyName)
    {
        propertyChanged(propertyName);
    }

private:
    static CoreContext* current_;
    std::shared_ptr<Document> document_;
    std::shared_ptr<Workspace> workspace_;
    std::shared_ptr<Viewport> viewport_;
    std::shared_ptr<ParameterSets> parameterSets_;
    std::unique_ptr<MessageManager> MessageManager_;
};

#endif // _CoreContext_h_
