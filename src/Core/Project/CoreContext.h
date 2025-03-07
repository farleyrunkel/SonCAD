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
    static CoreContext* current() noexcept
    {
        return current_;
    }

    static void setCurrent(CoreContext* context)
    {
        delete current_; // 手动释放旧实例
        current_ = context;
    }

    // Document 属性
    virtual std::shared_ptr<Document> document() const
    {
        return document_;
    }

    virtual void setDocument(const std::shared_ptr<Document>& document)
    {
        document_ = document;

        raisePropertyChanged("document");
        raisePropertyChanged("undoHandler");
        raisePropertyChanged("layers");

        //if(document_ && document_->layers())
        //{
        //    document_->layers()->onActivated();
        //}

        // 检查 Workspace 是否属于新 Document

		auto workspaces = document_->workspaces();
        auto found = std::find(workspaces.begin(), workspaces.end(), workspace_);
        if(document_ && found == workspaces.end())
        {
			auto workspace = workspaces.empty() 
                ? std::make_shared<Workspace>() 
                : workspaces.front();
            setWorkspace(workspace);
        }
    }

    // Workspace 属性
    virtual std::shared_ptr<Workspace> workspace() const
    {
        return workspace_;
    }

    virtual void setWorkspace(const std::shared_ptr<Workspace>& workspace)
    {
        workspace_ = workspace;

        auto viewports = workspace_->viewports();
		auto viewport = viewports.empty() 
            ? std::make_shared<Viewport>() 
            : viewports.front();
		setViewport(viewport);

        raisePropertyChanged("workspace");
    }

    virtual std::shared_ptr<Viewport> viewport() const
    {
        return viewport_;
    }

    virtual void setViewport(const std::shared_ptr<Viewport>& viewport)
    {
        viewport_ = viewport;
        raisePropertyChanged("viewport");
    }

    std::shared_ptr<LayerCollection> layers() const
    {
        return document_ ? document_->layers() : nullptr;
    }

    // MessageManager 属性（只读）
    std::shared_ptr<MessageManager> messageManager() const
    {
        return MessageManager_;
    }

    // Parameters 属性
    std::shared_ptr<ParameterSets> parameters()
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
    CoreContext()
    {
        current_ = this;
        MessageManager_ = std::make_shared<MessageManager>();
    }

    CoreContext(const CoreContext&) = delete;
    CoreContext& operator=(const CoreContext&) = delete;

    virtual ~CoreContext()
    {
        dispose(false);
    }

    virtual void dispose(bool disposing)
    {
        if(disposing)
        {
            MessageManager_.reset();
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
    std::shared_ptr<MessageManager> MessageManager_;
};

#endif // _CoreContext_h_
