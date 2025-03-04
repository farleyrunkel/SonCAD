// Copyright [2024] SunCAD

#ifndef SRC_IACT_COMMANDS_COMMANDHELPER_H_
#define SRC_IACT_COMMANDS_COMMANDHELPER_H_

#include <functional>

#include "Iact/Framework/Tool.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Workspace/Selection/SelectionManager.h"

class CommandHelper
{
public:
    static std::shared_ptr<Tool> GetCurrentTool()
    {
        return nullptr;
    };

    static std::shared_ptr<SelectionManager> GetSelectionManager()
    {
        return nullptr;
    };

    static void Invalidate() {}

    static bool StartTool(const std::shared_ptr<Tool>& theTool)
    {
        return false;
    };

    static bool CanStartTool()
    {
        return false;
    }

    static bool CanExecuteOnSingle(const std::function<void(std::shared_ptr<InteractiveEntity>, bool)>& predicate)
    {
        return false;
    }

    static bool CanExecuteOnMulti(const std::function<void(std::shared_ptr<InteractiveEntity>, bool)>& predicate)
    {
        return false;
    }

    static bool CanExecuteOnSingleSolid()
    {
        return false;
    }

    static bool CanExecuteOnMultiSolid()
    {
        return false;
    }

    static bool CanExecuteOnSingleSketch()
    {
        return false;
    }

    static bool CanExecuteOnMultiSketch()
    {
        return false;
    }

    static bool CanExecuteOnWorkspace()
    {
        return false;
    }

    static bool CanExecuteOnViewport()
    {
        return false;
    }

private:
    static std::shared_ptr<WorkspaceController> GetWorkspaceController()
    {
        return nullptr;
    };
};

#endif  // SRC_IACT_COMMANDS_COMMANDHELPER_H_
