// Copyright [2024] SunCAD

#include "Iact/Commands/CommandHelper.h"

#include "Core/Core.h"


    Handle(WorkspaceController) CommandHelper::GetWorkspaceController() {
        return Core::GetAppContext() ? Core::GetAppContext()->GetGetWorkspaceController() : nullptr;
    }

    Handle(ModelController) CommandHelper::DocumentController() {
        return Core::GetAppContext() ? Core::GetAppContext()->DocumentController() : nullptr;
    }

    //Tool* CommandHelper::currentTool() {
    //    return /*GetWorkspaceController() ? GetWorkspaceController()->currentTool() :*/ nullptr;
    //}

    //bool CommandHelper::startTool(Tool* tool) {
    //    qDebug() << "Debug: CommandHelper::startTool";
    //    return false; //GetWorkspaceController() && GetWorkspaceController()->startTool(tool);
    //}

    bool CommandHelper::CanExecuteOnViewport() {
        return false; /*Core::AppContext() && Core::AppContext()->viewportController()
            && Core::AppContext()->viewportController()->Viewport()*/;
    }

    bool CommandHelper::CanStartTool() {
        return false; /*GetWorkspaceController() != nullptr;*/
    }
