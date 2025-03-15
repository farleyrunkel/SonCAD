// Copyright [2024] SunCAD

#include "Core/CoreContext.h"

#include "Core/Topology/Model.h"

CoreContext* CoreContext::_Current = nullptr;

CoreContext::CoreContext()
{
	_Current = this;
}

void CoreContext::SetDocument(const Handle(Model)& doc)
{
    _Document = doc;

    if(_Document.IsNull())
    {
        return;
    }
    auto& workspaces = _Document->GetWorkspaces();

    auto it = std::find_if(workspaces.begin(), workspaces.end(), [this](const Handle(Workspace)& workspace) {
        return workspace == this->GetWorkspace();
    });

    if(it == workspaces.end())
    {
        SetWorkspace(workspaces.IsEmpty() ? new Workspace() : workspaces.First());
    }
}

Handle(Workspace) CoreContext::GetWorkspace()
{
    return _Workspace;
}

void CoreContext::SetWorkspace(const Handle(Workspace)& value)
{
    _Workspace = value;

	auto& viewports = _Workspace->GetViewports();
	SetViewport(viewports.IsEmpty() ? new Viewport : viewports.First());
}

void CoreContext::SetViewport(const Handle(Viewport)& value)
{
	_Viewport = value;
}
