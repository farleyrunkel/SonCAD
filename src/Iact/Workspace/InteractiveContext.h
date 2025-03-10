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
	InteractiveContext();
	virtual ~InteractiveContext();

	static InteractiveContext* current();

	std::shared_ptr<DocumentController> documentController() const;

	void setDocumentController(const std::shared_ptr<DocumentController>& documentController);

	std::shared_ptr<WorkspaceController> workspaceController() const;

	std::shared_ptr<ViewportController> viewportController() const;

	virtual void setWorkspace(const std::shared_ptr<Workspace>& workspace) override;

	virtual void setViewport(const std::shared_ptr<Viewport>& value) override;

private:
	std::shared_ptr<DocumentController> m_modelController;
	std::shared_ptr<ViewportController> m_viewportController; 
	std::shared_ptr<WorkspaceController> m_workspaceController;

	std::vector<Quantity_Color> _RecentUsedColors;
	std::shared_ptr<EditorState> myEditorState;

	const int _MaxScriptMruCount = 1;

private:
	static InteractiveContext* m_current;
};

#endif // !_InteractiveContext_h
