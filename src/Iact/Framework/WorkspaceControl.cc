// Copyright [2024] SunCAD
#include "Iact/Framework/WorkspaceControl.h"

#include "Iact/HudElements/HudElement.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/WorkspaceController.h"

WorkspaceControl::WorkspaceControl()
{}

Handle(WorkspaceController) WorkspaceControl::GetWorkspaceController() const
{
	return _WorkspaceController;
}

void WorkspaceControl::SetWorkspaceController(const Handle(WorkspaceController)& WorkspaceController)
{
	_WorkspaceController = WorkspaceController;
}

NCollection_Vector<Handle(WorkspaceControl)> WorkspaceControl::GetChildren() const
{
	return {};
}

void WorkspaceControl::Add(IHudElement* hudElement)
{
	if(hudElement == nullptr)
	{
		return;
	}
	// convert qlist contains function to std vector
	auto it = std::find(_HudElements.begin(), _HudElements.end(), hudElement);
	if(it != _HudElements.end())
	{
		return;
	}

	_HudElements.push_back(hudElement);
	//if (auto wc = App->AppContext()->GetWorkspaceController(); wc->hudManager()) {
	//	wc->hudManager()->AddElement(hudElement);
	//}
}

void WorkspaceControl::SetHintMessage(const QString& message)
{
	//auto hudManager = GetWorkspaceController()->hudManager();
	//if (hudManager)
	//	hudManager->SetHintMessage(message);
}

void WorkspaceControl::Add(Handle(VisualObject) visual)
{

	auto it = std::find(_VisualObjects.begin(), _VisualObjects.end(), visual);
	if(it != _VisualObjects.end())
	{
		return;
	}
	_VisualObjects.push_back(visual);
	GetWorkspaceController()->Invalidate();
}
