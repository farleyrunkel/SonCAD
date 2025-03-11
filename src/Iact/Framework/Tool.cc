#include "Iact/Framework/Tool.h"

#include <algorithm>

#include "Iact/Framework/ToolAction.h"
#include "Iact/Workspace/WorkspaceController.h"

// 构造函数
Tool::Tool() : WorkspaceControl()
{
}

// 析构函数
Tool::~Tool()
{
}

void Tool::addAction(const std::shared_ptr<ToolAction>& action)
{
    if(action)
    {
        m_toolActions.push_back(action);
    }
}
void Tool::removeAction(const std::shared_ptr<ToolAction>& action)
{
    auto it = std::find(m_toolActions.begin(), m_toolActions.end(), action);
    if(it != m_toolActions.end())
    {
        m_toolActions.erase(it);
    }
}

bool Tool::start()
{
    if(onStart())
    {
        for(const auto& action : m_toolActions)
        {
            if(action)
            {
                action->start();
            }
        }
        return true;
    }
    return false;
}

// 停止工具
void Tool::stop()
{
    m_isActive = false;
    onStop();

    workspaceController()->removeTool(shared_from_this());
    workspaceController()->invalidate();
}

bool Tool::cancel(bool force) 
{
    if(!onCancel() && !force)
        return false;

    if(m_isActive)
        stop();
    return true;
}

std::shared_ptr<ToolAction> Tool::currentAction() const
{
    return m_toolActions.empty() ? nullptr : m_toolActions.front();
}

// 默认启动逻辑
bool Tool::onStart()
{
    // 可由子类重写
    return true;
}

// 默认停止逻辑
void Tool::onStop()
{
    // 可由子类重写
}

bool Tool::onCancel()
{
    return true;
}

void Tool::stopAction(const std::shared_ptr<ToolAction>& toolAction)
{
    if(toolAction == nullptr)
        return;

    if(!m_toolActions.empty())
        m_toolActions.erase(std::remove(m_toolActions.begin(), m_toolActions.end(), toolAction), m_toolActions.end());

    toolAction->stop();
}

void Tool::stopAllActions()
{
    if(!m_toolActions.empty())
    {
        // 复制指针或引用，避免修改正在遍历的 `_Actions`
        auto actions = std::move(m_toolActions);
        m_toolActions.clear();

        // 遍历副本并停止所有动作
        for(const auto& action : actions)
        {
            stopAction(action);
        }
    }
}
