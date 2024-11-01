// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

#include <QObject>

#include <Aspect_NeutralWindow.hxx>
#include <Aspect_RenderingContext.hxx>
#include <Standard_Integer.hxx>
#include <V3d_View.hxx>
#include <AIS_ViewCube.hxx>
#include <V3d_TypeOfOrientation.hxx>
#include <Graphic3d_MaterialAspect.hxx>

#include "Core/Viewport.h"
#include "Iact/Workspace/WorkspaceController.h"

class ViewportController : public QObject {
    Q_OBJECT

public:
    explicit ViewportController(QObject* parent = nullptr) : QObject(parent) {}

    explicit ViewportController(Viewport* viewport, WorkspaceController* workspacecontroller);

    Viewport* viewport() const { return m_viewport; }

    Handle(V3d_View) view() const {
        return this->viewport() ? this->viewport()->view() : nullptr;
    }

    Handle(AIS_ViewCube) viewCube() const {
        return m_viewCube;
    }

    const Handle(Aspect_Window)& window() const {
        return !view().IsNull() ? view()->Window() : nullptr;
    }

    void setWindow(const Handle(Aspect_Window)& theWindow,
        const Aspect_RenderingContext theContext = NULL);

     QString dumpInfo(bool theIsBasic, bool theToPrint);

     WorkspaceController* workspaceController() const { return m_workspaceController; }

     enum class PredefinedViews {
         Top,
         Bottom,
         Left,
         Right,
         Front,
         Back,
         WorkingPlane
     };

     enum MouseMoveMode {
         None,
         Panning,
         Rotating,
         Twisting,
         Zooming
     };

     void mouseMove(const QPointF& pos, Qt::KeyboardModifiers modifiers, MouseMoveMode mode = MouseMoveMode::None) {};
     void mouseDown(Qt::KeyboardModifiers modifiers) {};
     void mouseUp(Qt::KeyboardModifiers modifiers) {};
     void startEditing() {};
     void startRubberbandSelection() {};  // Add necessary parameters
     void zoom(const QPointF& pos, double delta) {};
     void rotate(double deltaX, double deltaY, double deltaZ) {};

     bool isInRubberbandSelection() const {};  // Returns whether rubberband selection is active
     bool isSelecting() const {};              // Returns whether selection mode is active
     bool isLockedToPlane() const {};            // Returns whether the view is locked to a specific plane
     //--------------------------------------------------------------------------------------------------

     void setPredefinedView(PredefinedViews predefinedView);

private:
    void init() { viewport()->init(true); }

    void setViewCube(bool isVisible);

    void setViewCube(bool isVisible, uint32_t size, double duration);

private:
    Viewport* m_viewport;
    Handle(AIS_ViewCube) m_viewCube = nullptr;
    bool _LockedToPlane = false;
    WorkspaceController* m_workspaceController;
};
#endif // SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
