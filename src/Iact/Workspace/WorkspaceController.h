#ifndef _WorkspaceController_h
#define _WorkspaceController_h

#include <chrono>
#include <thread>
#include <vector>

#include <AIS_InteractiveObject.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
 
#include "Core/Project/Viewport.h"
#include "Core/Project/Workspace.h"
#include "Iact/HudElements/HudManager.h"
#include "Iact/Visual/VisualObjectManager.h"
#include "Iact/Workspace/Selection/SelectionManager.h"
#include "Iact/Workspace/ViewportController.h"
#include "Occt/AisExtensions/AISX_Grid.h"

class WorkspaceController : public std::enable_shared_from_this<WorkspaceController>
{
public:
	WorkspaceController();
	WorkspaceController(const std::shared_ptr<Workspace>& value);

	void setActiveViewport(const std::shared_ptr<Viewport>& value);
	std::shared_ptr<ViewportController> getViewController(const std::shared_ptr<Viewport>& value);

	void initWorkspace();

	void initVisualSettings();

	void updateGrid();

	std::shared_ptr<Workspace> workspace() const
	{
		return m_workspace;
	}

	void invalidate() {}

private:
	std::shared_ptr<Workspace> m_workspace;
	std::shared_ptr<Viewport> m_activeViewport;

	std::shared_ptr<SelectionManager> m_selectionManager;
	std::shared_ptr<VisualObjectManager> m_visualObjectManager;
	std::shared_ptr<HudManager> m_hudManager;

	bool m_lockWorkingPlane;
	bool m_isSelecting;
	gp_Pnt m_cursorPosition;
	gp_Pnt2d m_cursorPosition2d;

	std::vector<std::shared_ptr<ViewportController>> m_viewportControllers;
	std::thread m_redrawTimer;

	Handle(AISX_Grid) m_grid;
	gp_XY m_lastGridSize;
	bool m_gridNeedsUpdate;
	std::vector<Handle(AIS_InteractiveObject)> m_objects;
 };

#endif // !_WorkspaceController_h
