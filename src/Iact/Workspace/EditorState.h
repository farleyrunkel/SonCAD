// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_EDITORSTATE_H_
#define IACT_WORKSPACE_EDITORSTATE_H_

#include <string>

#include <Standard_Transient.hxx>

#include "Iact/Workspace/ViewportController.h"

// Forward declarations
class Tool;
class WorkspaceController;

DEFINE_STANDARD_HANDLE(EditorState, Standard_Transient)

class EditorState : Standard_Transient
{
public:
	EditorState() {}

private:
	std::string myActiveTool;
	bool mySketchGroupVisible;
	std::string myActiveSketchTool;
	ViewportController::RubberbandSelectionMode _RubberbandSelectionMode;
	bool _RubberbandIncludeTouched;

	Handle(WorkspaceController) myWorkspaceController;

	bool _SnapToGridSelected;
	bool _SnapToVertexSelected;
	bool _SnapToEdgeSelected;
	bool _SnappingEnabled;
};

#endif // IACT_WORKSPACE_EDITORSTATE_H_
