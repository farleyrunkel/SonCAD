// Copyright [2024] SunCAD

#ifndef SRC_IACT_TOOLACTION_POINTACTION_H_
#define SRC_IACT_TOOLACTION_POINTACTION_H_

#include "Iact/Framework/ToolAction.h"
#include "Iact/Workspace/MouseEventData.h"

#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <QMessageBox>

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

    bool onMouseMove(MouseEventData* data) override;;
    bool onMouseDown(MouseEventData* data) override { return false; };
    bool onMouseUp(MouseEventData* data) override { return false; };

 private:
     void ensureMarker() {}
     void processMouseInput(MouseEventData* data);

 signals:
    void preview(EventArgs* args);
    void finished();

private:
    bool m_isFinished;
};

#endif  // SRC_IACT_TOOLACTION_POINTACTION_H_
