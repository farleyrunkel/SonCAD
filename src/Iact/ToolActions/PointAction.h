// Copyright [2024] SunCAD

#ifndef SRC_IACT_TOOLACTION_POINTACTION_H_
#define SRC_IACT_TOOLACTION_POINTACTION_H_

#include <QMessageBox>

#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>

#include "Iact/Visual/Marker.h"
#include "Iact/Framework/ToolAction.h"
#include "Iact/Workspace/MouseEventData.h"

class PointAction : public ToolAction {
    Q_OBJECT

 public:
    struct EventArgs {
        gp_Pnt Point;
        gp_Pnt2d PointOnPlane;
        //MouseEventData MouseEventData{ get; init; }
        //gp_Pnt MarkerPosition{ get; set; }
    };

 public:
    explicit PointAction();;
 
 protected:
    bool onStart() override;

    bool onMouseMove(MouseEventData* data) override;
    bool onMouseDown(MouseEventData* data) override;
    bool onMouseUp(MouseEventData* data) override;

 private:
     void ensureMarker() {}
     void processMouseInput(MouseEventData* data);

 signals:
    void preview(EventArgs* args);
    void finished(EventArgs* args);

private:
    bool m_isFinished;
    Marker* _Marker;
};

#endif  // SRC_IACT_TOOLACTION_POINTACTION_H_
