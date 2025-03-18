// Copyright [2024] SunCAD

#include "Iact/Workspace/WorkspaceController.h"

#include "Comm/BaseObject.h"
#include "Core/Workspace.h"
#include "Iact/Framework/Tool.h"

WorkspaceController::WorkspaceController()
{}

bool WorkspaceController::StartTool(const Handle(Tool)& tool)
{
	tool->SetWorkspaceController(this);

	tool->Start();

    return false;
}

Handle(Tool) WorkspaceController::CurrentTool()
{
    return nullptr;
}

Handle(Workspace) WorkspaceController::GetWorkspace()
{
    return _Workspace;
}

// GetViewController

Handle(ViewportController) WorkspaceController::GetViewController(int index)
{
    return _ViewControllers[index];
}

Handle(ViewportController) WorkspaceController::GetViewController(const Handle(Viewport)& viewport)
{
    if(viewport.IsNull())
    {
        return nullptr;
    }

    auto it = std::find_if(_ViewControllers.begin(), _ViewControllers.end(),
                           [viewport](const auto& vc) {
        return vc->GetViewport() == viewport;
    });

	return (it == _ViewControllers.end()) ? nullptr: *it;
}

void WorkspaceController::InitWorkspace()
{
	_Workspace->InitV3dViewer();
	_Workspace->InitAisContext();

    for(auto& view : _Workspace->GetViewports())
    {
        Handle(ViewportController) viewCtrl = new ViewportController(view, this);
		_ViewControllers.push_back(viewCtrl);
    }
}

void WorkspaceController::SetActiveViewport(const Handle(Viewport)& viewport)
{
	_ActiveViewport = viewport;
}

Handle(Viewport) WorkspaceController::ActiveViewport() const
{
	return _ActiveViewport;
}

std::vector<Handle(WorkspaceControl)> WorkspaceController::EnumerateControls()
{
    qDebug() << "Debug: m_workspaceController::enumerateControls";
    std::vector<Handle(WorkspaceControl)> controls;

    if(m_currentTool)
    {
        controls.push_back(m_currentTool);
    }

    if(m_currentEditor)
    {
        controls.push_back(m_currentEditor);
    }

    return controls;
}

void WorkspaceController::MouseMove(const Handle(ViewportController)& VC, const Graphic3d_Vec2d& pos, Aspect_VKeyFlags keys) 
{
    qDebug() << "Debug: m_workspaceController::MouseMove: " << pos;
    for(const auto& handler : EnumerateControls())
    {
        if(handler->OnMouseMove(m_mouseEventData)) {
        }
    }
}

void WorkspaceController::MouseDown(const Handle(ViewportController)& VC, Aspect_VKeyFlags keys) 
{}

void WorkspaceController::MouseUp(const Handle(ViewportController)& VC, Aspect_VKeyFlags keys)
{}
