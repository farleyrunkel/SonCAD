#ifndef _Tool_h
#define _Tool_h

#include <memory>
#include <vector>

#include <boost/signals2.hpp>

#include "Iact/Framework/ToolAction.h"
#include "Iact/Framework/WorkspaceControl.h"
#include "Iact/Workspace/MouseEventData.h"

class WorkspaceController;
class InteractiveEntity;

class Tool : public WorkspaceControl, public std::enable_shared_from_this<Tool>
{
public:
    // 构造函数和析构函数
    explicit Tool();
    virtual ~Tool();

public:
    // 工具生命周期控制
    bool start();
    void stop();
    bool cancel(bool force);

    std::shared_ptr<ToolAction> currentAction() const;

    void addAction(const std::shared_ptr<ToolAction>& action);
    void removeAction(const std::shared_ptr<ToolAction>& action);

protected:
    // 供子类重写的启动和停止逻辑
    virtual bool onStart();
    virtual void onStop();
    bool onCancel();

    void stopAction(const std::shared_ptr<ToolAction>& toolAction);

    void stopAllActions();

public:
    boost::signals2::signal<void(const ToolAction&)> sig_toolActionChanged;

private:
    std::vector<std::shared_ptr<ToolAction>> m_toolActions;
    bool m_isActive;
};

#endif // !_Tool_h
