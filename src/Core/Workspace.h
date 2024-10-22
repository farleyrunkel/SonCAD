// Copyright [2024] SunCAD

#ifndef SRC_CORE_WORKSPACE_H_
#define SRC_CORE_WORKSPACE_H_

#include <QObject>
#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>
#include <vector>

class Workspace : public QObject {
    Q_OBJECT

public:
    Workspace();
    ~Workspace() {};

    // Initialize 3D viewer and context
    void initViewer();

    // Getters
    Handle(V3d_Viewer) v3dViewer() const;
    Handle(AIS_InteractiveContext) aisContext() const;

    bool needsRedraw() const;
    bool needsImmediateRedraw() const;

    // Setters
    void setNeedsRedraw(bool value);
    void setNeedsImmediateRedraw(bool value);

    // Viewports management
    // std::vector<Viewport*>& viewports();

    // Model management
    //const Model* model() const;
    //void setModel(Model* model);

private:
    Handle(V3d_Viewer) m_v3dViewer;  // 3D viewer handle
    Handle(AIS_InteractiveContext) m_aisContext;  // AIS context handle

    bool m_gridEnabled;  // Grid enabled status
    bool m_needsRedraw;  // Flag to check if redraw is needed
    bool m_needsImmediateRedraw;  // Flag for immediate redraw

    // std::vector<Viewport*> m_viewports;  // List of viewports
    // Model* m_model;  // The active model
};

#endif  // SRC_CORE_WORKSPACE_H_
