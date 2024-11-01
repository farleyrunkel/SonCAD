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
#include "Core/Project/WorkingContext.h"

class Model;
class Viewport;

class Workspace : public QObject {
    Q_OBJECT

public:
    Workspace();
    Workspace(Model* model);;
    ~Workspace() {};

    // Initialize 3D viewer and context
    void initV3dViewer();
    void initAisContext();

    void _ApplyWorkingContext();

    // Getters
    Handle(V3d_Viewer) v3dViewer() const;
    Handle(AIS_InteractiveContext) aisContext() const;

    bool needsRedraw() const;
    bool needsImmediateRedraw() const;

    // Setters
    void setNeedsRedraw(bool value);
    void setNeedsImmediateRedraw(bool value);

    const gp_Pln& workingPlane() const {
        return  gp_Pln();//_CurrentWorkingContext.WorkingPlane;
    }

    void setWorkingPlane(const gp_Pln& value) {
        //_CurrentWorkingContext.WorkingPlane = value;
        //Model::MarkAsUnsaved();
        //_ApplyWorkingContext();
    }

    // Viewports management
    QVector<Viewport*>& viewports() { return m_viewports; }

    // Model management
    Model* model() const { return m_model ; }
    void setModel(Model* model) { m_model = model; }

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

    gp_Pln WorkingPlane; 
    WorkingContext* _CurrentWorkingContext;
};

#endif  // SRC_CORE_WORKSPACE_H_
    