// Copyright [2024] SunCAD

#ifndef IACT_FRAMEWORK_EDITOR_H_
#define IACT_FRAMEWORK_EDITOR_H_

#include <Standard_Handle.hxx>

#include "Iact/Framework/WorkspaceControl.h"

DEFINE_STANDARD_HANDLE(Editor, WorkspaceControl);

class Editor : public WorkspaceControl
{
public:
	explicit Editor();

	void StopTool();
};

#endif  // IACT_FRAMEWORK_EDITOR_H_
