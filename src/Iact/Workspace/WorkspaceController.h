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
#include "Iact/Framework/Editor.h"
#include "Iact/Framework/Tool.h"
#include "Iact/Framework/Tool.h"
#include "Iact/HudElements/HudManager.h"
#include "Iact/Visual/VisualObjectManager.h"
#include "Iact/Workspace/Selection/SelectionManager.h"
#include "Iact/Workspace/ViewportController.h"
#include "Occt/AisExtensions/AISX_Grid.h"

class WorkspaceController : public std::enable_shared_from_this<WorkspaceController>
{
public:
	WorkspaceController(const std::shared_ptr<Workspace>& value);

	std::shared_ptr<ViewportController> getViewController(int idx) const;
	std::shared_ptr<ViewportController> getViewController(const std::shared_ptr<Viewport>& value);

	// currentTool
	std::shared_ptr<Tool> currentTool() const { return m_currentTool; }
	void setCurrentTool(const std::shared_ptr<Tool>& value) { m_currentTool = value; }

	// remove Tool
	void removeTool(const std::shared_ptr<Tool>& value) {}

	// start Tool
	void startTool(const std::shared_ptr<Tool>& value) {}

	// cancel tool
	void cancelTool(const std::shared_ptr<Tool>& value) {}

	void setActiveViewport(const std::shared_ptr<Viewport>& value);

	void initWorkspace();

	std::shared_ptr<Workspace> workspace() const;

	void invalidate(bool immediateOnly, bool forceRedraw = false);

	void invalidate() {}

	auto visualObjects()
	{
		return m_visualObjectManager;
	}

private:
	void workspace_GridChanged(Workspace* sender);
	void viewport_ViewportChanged(Viewport* sender);
	void redraw();
	void updateGrid();
	void initVisualSettings();
	void recalculateGridSize();
	void updateParameter();
	void redrawTimer_Tick();

private:
	std::shared_ptr<Tool> m_currentTool;
	std::shared_ptr<Editor> m_currentEditor;

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
	QTimer* m_redrawTimer;

	Handle(AISX_Grid) m_grid;
	gp_XY m_lastGridSize;
	bool m_gridNeedsUpdate;
	std::vector<Handle(AIS_InteractiveObject)> m_objects;
};

#endif // !_WorkspaceController_h
