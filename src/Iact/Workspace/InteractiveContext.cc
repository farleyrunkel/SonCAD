// Copyright [2024] SunCAD

#include "Iact/Workspace/InteractiveContext.h"

#include <QString>

#include "Comm/BaseObject.h"
#include "Core/CoreContext.h"
#include "Iact/Workspace/ModelController.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"

InteractiveContext::InteractiveContext()
    : CoreContext(),
    _DocumentController(new ModelController()),
    _WorkspaceController(nullptr),
    _ViewportController(nullptr)
{
    Initialize();
}

InteractiveContext::~InteractiveContext()
{
    // 释放资源
    if(_DocumentController)
    {
        _DocumentController->Dispose();
        _DocumentController = nullptr;
    }
    if(_WorkspaceController)
    {
        _WorkspaceController->Dispose();
        _WorkspaceController = nullptr;
    }
    _ViewportController = nullptr;
}

// ModelController getter/setter

Handle(ModelController) InteractiveContext::GetDocumentController() const
{
    return _DocumentController;
}

void InteractiveContext::SetDocumentController(const Handle(ModelController)& controller)
{
    if(_DocumentController != controller)
    {
        if(_DocumentController)
        {
            _DocumentController->Dispose();
        }
        _DocumentController = controller;

    }
}

// WorkspaceController getter/setter

Handle(WorkspaceController) InteractiveContext::GetWorkspaceController() const
{
    return _WorkspaceController;
}

void InteractiveContext::SetWorkspaceController(const Handle(WorkspaceController)& controller)
{
    if(_WorkspaceController != controller)
    {
        if(_WorkspaceController)
        {
            _WorkspaceController->Dispose();
        }
        _WorkspaceController = controller;

    }
}

// ViewportController getter/setter

Handle(ViewportController) InteractiveContext::GetViewportController() const
{
    return _ViewportController;
}

void InteractiveContext::SetViewportController(const Handle(ViewportController)& controller)
{
    if(_ViewportController != controller)
    {
        _ViewportController = controller;

    }
}

// RecentUsedColors getter

QList<QColor> InteractiveContext::RecentUsedColors() const
{
    return _RecentUsedColors;
}

// RecentUsedScripts getter

QList<QString> InteractiveContext::RecentUsedScripts() const
{
    return _RecentUsedScripts;
}

// 添加脚本到最近使用列表

void InteractiveContext::AddToScriptMruList(const QString& filePath)
{
    int index = _RecentUsedScripts.indexOf(filePath);
    if(index >= 0)
    {
        _RecentUsedScripts.move(index, 0);  // 移动到列表顶部
        _RecentUsedScripts[0] = filePath;
    }
    else
    {
        if(_RecentUsedScripts.size() >= _MaxScriptMruCount)
        {
            _RecentUsedScripts.removeLast();  // 删除最老的脚本
        }
        _RecentUsedScripts.prepend(filePath);
    }

}
