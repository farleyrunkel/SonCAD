// Copyright [2024] SonCAD

#ifndef SRC_CORE_WORKSPACE_H_
#define SRC_CORE_WORKSPACE_H_

#include <QObject>

#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>

class Workspace : public QObject {
    Q_OBJECT

 public:
    Workspace();

    void initViewer();

    Handle(V3d_Viewer) V3dViewer() const;

 private:
    Handle(V3d_Viewer) v3dViewer;
    Handle(AIS_InteractiveContext) aisContext;
    bool gridEnabled;
};

#endif  // SRC_CORE_WORKSPACE_H_
