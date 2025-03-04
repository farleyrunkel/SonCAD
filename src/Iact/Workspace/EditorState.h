// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_EDITORSTATE_H_
#define IACT_WORKSPACE_EDITORSTATE_H_

#include <string>

#include "Iact/Workspace/ViewportController.h"
#include "Comm/BaseObject.h"

// Forward declarations
class Tool;
class WorkspaceController;

class EditorState : public enable_property_changed_signal
{
public:
	EditorState() {}

private:
	std::string myActiveTool;
	bool mySketchGroupVisible;
	std::string myActiveSketchTool;
	ViewportController::RubberbandSelectionMode _RubberbandSelectionMode;
	bool _RubberbandIncludeTouched;

	std::shared_ptr<WorkspaceController> myWorkspaceController;

	bool _SnapToGridSelected;
	bool _SnapToVertexSelected;
	bool _SnapToEdgeSelected;
	bool _SnappingEnabled;
};

#endif // IACT_WORKSPACE_EDITORSTATE_H_
