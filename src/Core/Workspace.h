// Copyright [2024] SunCAD

#ifndef SRC_CORE_WORKSPACE_H_
#define SRC_CORE_WORKSPACE_H_

#include <QObject>
#include <QList>

#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_DisplayMode.hxx>
#include <Prs3d_LineAspect.hxx>

#include "Comm/BaseObject.h"
#include "Core/Project/VisualStyles.h"
#include "Core/Extensions/ColorExtensions.h"
#include "Occt/ValueTypes/Pln.h"

class Model;
class Viewport;
class WorkingContext;

namespace Sun {

class Workspace : public BaseObject 
{
    Q_OBJECT
    Q_PROPERTY(QList<Viewport*> Viewports READ viewports)
    Q_PROPERTY(Handle(V3d_Viewer) V3dViewer READ v3dViewer)
    Q_PROPERTY(Handle(AIS_InteractiveContext) AisContext READ aisContext)
    Q_PROPERTY(bool NeedsRedraw READ needsRedraw WRITE setNeedsRedraw)
    Q_PROPERTY(bool NeedsImmediateRedraw READ needsImmediateRedraw WRITE setNeedsImmediateRedraw)
    Q_PROPERTY(Model* Model READ model)
    Q_PROPERTY(bool GridEnabled READ gridEnabled WRITE setGridEnabled)
    Q_PROPERTY(GridTypes GridType READ gridType WRITE setGridType)
    Q_PROPERTY(double GridStep)
    Q_PROPERTY(double GridRotation)
    Q_PROPERTY(int GridDivisions)
    Q_PROPERTY(Pln _WorkingPlane)
    Q_PROPERTY(WorkingContext WorkingContext)
    Q_PROPERTY(WorkingContext GlobalWorkingContext)

public:
    enum GridTypes {
        Rectangular,
        Circular
    };

 public:
    Workspace();
    Workspace(Model* model);;
    ~Workspace() {};

    // Initialize 3D viewer and context
    void initV3dViewer();
    void initAisContext();

    bool gridEnabled() const { return _GridEnabled; }
    void setGridEnabled(bool value);

    GridTypes gridType() const;
    void setGridType(GridTypes) { return; }

    WorkingContext* workingContext() const;

    const gp_Pln& workingPlane() const {
        return gp_Pln();//_CurrentWorkingContext.WorkingPlane;
    }

    void setWorkingPlane(const gp_Pln& value) {
        //_CurrentWorkingContext.WorkingPlane = value;
        //Model::MarkAsUnsaved();
        //_ApplyWorkingContext();
    }

    // Viewports management
    QList<Viewport*>& viewports() { return _Viewports; }
    Handle(V3d_Viewer) v3dViewer() const;
    Handle(AIS_InteractiveContext) aisContext() const;

    bool needsRedraw() const;
    void setNeedsRedraw(bool value);

    bool needsImmediateRedraw() const;
    void setNeedsImmediateRedraw(bool value);

    // Model management
    Model* model() const { return _Model ; }

signals:
    void GridChanged(Sun::Workspace*);

private:
     void init();
     void _ApplyWorkingContext();
     void _RaiseGridChanged() {
         emit GridChanged(this);
     }

private:
    Handle(V3d_Viewer) _V3dViewer;  // 3D viewer handle
    Handle(AIS_InteractiveContext) _AisContext;  // AIS context handle

    bool _GridEnabled;  // Grid enabled status
    bool _NeedsRedraw;  // Flag to check if redraw is needed
    bool _NeedsImmediateRedraw;  // Flag for immediate redraw

    QList<Viewport*> _Viewports;  // List of viewports
    Model* _Model;  // The active model

    Pln _WorkingPlane;
    WorkingContext* _CurrentWorkingContext;
    WorkingContext* _GlobalWorkingContext;
};

}
#endif  // SRC_CORE_WORKSPACE_H_
