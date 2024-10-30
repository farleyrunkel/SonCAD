// Copyright [2024] SunCAD

#ifndef SRC_CORE_WORKSPACE_H_
#define SRC_CORE_WORKSPACE_H_

#include <vector>

#include <QObject>
#include <QVector>

#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_DisplayMode.hxx>
#include <Prs3d_LineAspect.hxx>

#include "Core/Project/VisualStyles.h"
#include "Core/Extensions/ColorExtensions.h"

class Model;
class Viewport;

class Workspace : public QObject {
    Q_OBJECT

public:
    Workspace();
    ~Workspace() {};

    // Initialize 3D viewer and context
    void initV3dViewer();
    void initAisContext() {
        if (m_v3dViewer.IsNull())
            initV3dViewer();

        if (m_aisContext.IsNull())
        {
            m_aisContext = new AIS_InteractiveContext(m_v3dViewer);
            m_aisContext->UpdateCurrentViewer();
        }

        m_aisContext->SetAutoActivateSelection(true);
        m_aisContext->SetToHilightSelected(false);
        m_aisContext->SetPickingStrategy(SelectMgr_PickingStrategy_OnlyTopmost);
        m_aisContext->SetDisplayMode((int)AIS_Shaded, false);
        m_v3dViewer->DisplayPrivilegedPlane(false, 1.0);
        m_aisContext->EnableDrawHiddenLine();

        // Reinit ais parameters
        _ApplyWorkingContext();
        m_aisContext->SetPixelTolerance(2);

        auto drawer = m_aisContext->DefaultDrawer();
        drawer->SetWireAspect(new Prs3d_LineAspect(ColorExtensions::toQuantityColor(Colors::Selection), Aspect_TOL_SOLID, 1.0));
        drawer->SetTypeOfHLR(Prs3d_TypeOfHLR::Prs3d_TOH_PolyAlgo);
    }

    void _ApplyWorkingContext()
    {
        if (!m_aisContext.IsNull())
        {
            // m_v3dViewer->SetPrivilegedPlane(_CurrentWorkingContext.WorkingPlane.Position);
        }
    }

    // Getters
    Handle(V3d_Viewer) v3dViewer() const;
    Handle(AIS_InteractiveContext) aisContext() const;

    bool needsRedraw() const;
    bool needsImmediateRedraw() const;

    // Setters
    void setNeedsRedraw(bool value);
    void setNeedsImmediateRedraw(bool value);

    // Viewports management
    QVector<Viewport*>& viewports() { return m_viewports; }

    // Model management
    Model* model() const {
        return m_model ;
    }
    void setModel(Model* model) {
        m_model = model;
    }
signals:
    void gridChanged();

private:
    Handle(V3d_Viewer) m_v3dViewer;  // 3D viewer handle
    Handle(AIS_InteractiveContext) m_aisContext;  // AIS context handle

    bool m_gridEnabled;  // Grid enabled status
    bool m_needsRedraw;  // Flag to check if redraw is needed
    bool m_needsImmediateRedraw;  // Flag for immediate redraw

    QVector<Viewport*> m_viewports;  // List of viewports
    Model* m_model;  // The active model
};

#endif  // SRC_CORE_WORKSPACE_H_
