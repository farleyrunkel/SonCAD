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
	InteractiveContext();;
	virtual ~InteractiveContext() {};

	static InteractiveContext* current()
	{
		return m_current;
	}

	std::shared_ptr<DocumentController> documentController() const
	{
		return m_modelController;
	}

private:
	std::shared_ptr<DocumentController> m_modelController;
	std::shared_ptr<ViewportController> myViewportController;
	std::shared_ptr<WorkspaceController> myWorkspaceController;

	std::vector<Quantity_Color> _RecentUsedColors;
	std::shared_ptr<EditorState> myEditorState;

	const int _MaxScriptMruCount = 1;

private:
	static InteractiveContext* m_current;
};

#endif // !_InteractiveContext_h
