#ifndef _InteractiveContext_h
#define _InteractiveContext_h

#include <cmath>

#include <Quantity_Color.hxx>

#include "Core/Project/CoreContext.h"
#include "Iact/Workspace/EditorState.h"
#include "Iact/Workspace/ModelController.h"

class ViewportController;
class WorkspaceController;

class InteractiveContext : public CoreContext
{
public:
	InteractiveContext() {};
	virtual ~InteractiveContext() {};

	static InteractiveContext* Current()
	{
		return myCurrent;
	}

private:
	Handle(ModelController) myModelController;
	Handle(ViewportController) myViewportController;
	Handle(WorkspaceController) myWorkspaceController;

	std::vector<Quantity_Color> _RecentUsedColors;
	Handle(EditorState) myEditorState;

	const int _MaxScriptMruCount = 1;

private:
	static InteractiveContext* myCurrent;
 };

#endif // !_InteractiveContext_h
