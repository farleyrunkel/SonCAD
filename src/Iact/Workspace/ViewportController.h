// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

// Qt includes
#include <QObject>

// Occt includes
#include <AIS_ViewCube.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <Aspect_RenderingContext.hxx>
#include <Graphic3d_MaterialAspect.hxx>
#include <Standard_Integer.hxx>
#include <V3d_TypeOfOrientation.hxx>
#include <V3d_View.hxx>

// Project includes
#include "Core/Viewport.h"
#include "Iact/Workspace/WorkspaceController.h"

class Sun_ViewportController : public QObject
{
	Q_OBJECT

public:
	enum class PredefinedViews
	{
		Top,
		Bottom,
		Left,
		Right,
		Front,
		Back,
		WorkingPlane
	};

	enum MouseMoveMode { None, Panning, Rotating, Twisting, Zooming };

public:
	explicit Sun_ViewportController(Sun_Viewport* Viewport,
									Sun_WorkspaceController* workspacecontroller);

	Sun_Viewport* Viewport() const { return m_viewport; }

	Handle(V3d_View) View() const {
		return this->Viewport() ? this->Viewport()->View() : nullptr;
	}

	Handle(AIS_ViewCube) ViewCube() const { return m_viewCube; }

	const Handle(Aspect_Window)& Window() const {
		return !View().IsNull() ? View()->Window() : nullptr;
	}

	void SetWindow(const Handle(Aspect_Window)& theWindow,
				   const Aspect_RenderingContext theContext = nullptr);

	QString DumpInfo(bool theIsBasic, bool theToPrint);

	Sun_WorkspaceController* workspaceController() const {
		return m_workspaceController;
	}

	void mouseMove(const QPointF& pos, Qt::KeyboardModifiers modifiers,
				   MouseMoveMode mode = MouseMoveMode::None);
	void mouseDown(Qt::KeyboardModifiers modifiers);
	void mouseUp(Qt::KeyboardModifiers modifiers);
	void startEditing() {}
	void startRubberbandSelection() {}  // Add necessary parameters
	void zoom(const QPointF& pos, double delta) {}
	void rotate(double deltaX, double deltaY, double deltaZ) {}

	bool isInRubberbandSelection() const {
		return false;
	}  // Returns whether rubberband selection is active
	bool isSelecting() const {
		return false;
	}  // Returns whether selection mode is active
	bool isLockedToPlane() const {
		return false;
	}  // Returns whether the view is locked to a specific plane

	void setPredefinedView(PredefinedViews predefinedView);

private:
	void init() { Viewport()->init(true); }

	void setViewCube(bool isVisible);
	void setViewCube(bool isVisible, uint32_t size, double duration);

private:
	Sun_Viewport* m_viewport;
	Sun_WorkspaceController* m_workspaceController;
	Handle(AIS_ViewCube) m_viewCube;
	bool m_lockedToPlane;

	const int RubberbandFreehandSelectionThresholdSquared = 100;
};

#endif  // SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
