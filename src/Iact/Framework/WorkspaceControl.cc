// Copyright [2024] SunCAD

#include "Iact/Framework/WorkspaceControl.h"

#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Visual/VisualObject.h"
#include "Core/Core.h"



	WorkspaceControl::WorkspaceControl()
		: 
		_WorkspaceController(nullptr) {
	}

	Handle(WorkspaceController) WorkspaceControl::GetWorkspaceController() const {
		return _WorkspaceController;
	}

	void WorkspaceControl::SetWorkspaceController(const Handle(WorkspaceController)& WorkspaceController) {
		_WorkspaceController = WorkspaceController;
	}

	QList<Handle(WorkspaceControl)> WorkspaceControl::GetChildren() const {
		return {};
	}

	void WorkspaceControl::Add(IHudElement* hudElement) {
		if (hudElement == nullptr || _HudElements.contains(hudElement)) {
			return;
		}
		_HudElements.append(hudElement);
		//if (auto wc = Core::AppContext()->GetWorkspaceController(); wc->hudManager()) {
		//	wc->hudManager()->AddElement(hudElement);
		//}
	}

	void WorkspaceControl::SetHintMessage(const QString& message) {
		//auto hudManager = GetWorkspaceController()->hudManager();
		//if (hudManager)
		//	hudManager->SetHintMessage(message);
	}

	void WorkspaceControl::Add(Handle(VisualObject) visual) {
		if (_VisualObjects.contains(visual))
			return;
		_VisualObjects.append(visual);
		GetWorkspaceController()->Invalidate();
	}

