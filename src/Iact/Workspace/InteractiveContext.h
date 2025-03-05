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

	static InteractiveContext* current()
	{
		return myCurrent;
	}

	std::shared_ptr<ModelController> documentController() const
	{
		return myModelController;
	}

private:
	std::shared_ptr<ModelController> myModelController;
	std::shared_ptr<ViewportController> myViewportController;
	std::shared_ptr<WorkspaceController> myWorkspaceController;

	std::vector<Quantity_Color> _RecentUsedColors;
	std::shared_ptr<EditorState> myEditorState;

	const int _MaxScriptMruCount = 1;

private:
	static InteractiveContext* myCurrent;
 };

#endif // !_InteractiveContext_h
