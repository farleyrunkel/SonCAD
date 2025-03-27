// Copyright [2024] SunCAD

#include "Iact/Framework/Tool.h"

#include <algorithm>

#include "Iact/Framework/WorkspaceControl.h"
#include "Iact/Workspace/WorkspaceController.h"

Tool::Tool() 
	: WorkspaceControl()
{}

bool Tool::Start()
{
	if(OnStart())
	{
		_IsActive = true;
		GetWorkspaceController()->Invalidate();
		return true;
	}
	return false;
}

bool Tool::OnStart()
{
	return false;
}

bool Tool::Cancel(bool force)
{
	if(!OnCancel() && !force)
		return false;

	if(_IsActive)
		Stop();
	return true;
}

bool Tool::OnCancel()
{
	return true;
}

void Tool::Stop()
{
	_IsActive = false;
	OnStop();
	Cleanup();

	GetWorkspaceController()->RemoveTool(this);
	GetWorkspaceController()->Invalidate();
}

void Tool::OnStop()
{}

Handle(ToolAction) Tool::CurrentAction() const
{
	return _ToolActions.IsEmpty() ? nullptr : _ToolActions.First();
}

bool Tool::PrepareUndo()
{
	return Cancel(false);
}

void Tool::Cleanup()
{
	StopAllActions();
	//RestoreAllVisualShapes();
}

bool Tool::StartAction(Handle(ToolAction) toolAction, bool exclusive)
{
	auto it = std::find(_ToolActions.begin(), _ToolActions.end(), toolAction);
	if(it != _ToolActions.end())
	{
		return true;
	}
	try
	{
		if(exclusive)
		{
			StopAllActions();
		}

		if(!toolAction.IsNull())
		{
			toolAction->SetWorkspaceController(GetWorkspaceController());
			if(!toolAction->Start())
				return false;

			_ToolActions.SetValue(0, toolAction);
			ToolActionChanged(toolAction);
		}
		return true;
	}
	catch(const std::exception& e)
	{
		// std::cerr << "Starting tool action failed: " << e.what() << std::endl;
		return false;
	}
}

void Tool::StopAction(Handle(ToolAction) toolAction)
{
	if(toolAction.IsNull())
		return;

	if(!_ToolActions.IsEmpty())
	{
		std::remove(_ToolActions.begin(), _ToolActions.end(), toolAction);
		_ToolActions.EraseLast();
	}

	toolAction->Stop();
	emit ToolActionChanged(toolAction);
}

void Tool::StopAllActions()
{
	for(const auto& action : _ToolActions)
	{
		StopAction(action);
	}
	_ToolActions.Clear();
}

NCollection_Vector<Handle(WorkspaceControl)> Tool::GetChildren() const
{
	NCollection_Vector<Handle(WorkspaceControl)> children;
	for(const auto& action : _ToolActions)
	{
		children.Append(action);
	}
	return children;
}
