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
    class EventArgs {
    public:
        EventArgs() {}
        EventArgs(const gp_Pnt& p, const gp_Pnt2d& pp, const gp_Pnt& mp, std::shared_ptr<MouseEventData> m)
             : Point(p), PointOnPlane(pp), MarkerPosition(mp), MouseEventData(m) {}
        gp_Pnt Point;
        gp_Pnt2d PointOnPlane;
        std::shared_ptr<MouseEventData> MouseEventData;
        gp_Pnt MarkerPosition;
    };

 public:
    explicit PointAction();;
 
 protected:
    bool onStart() override;

    bool onMouseMove(const std::shared_ptr<MouseEventData>& data) override;
    bool onMouseDown(const std::shared_ptr<MouseEventData>& data) override;
    bool onMouseUp(const std::shared_ptr<MouseEventData>& data) override;

 private:
     void _EnsureMarker();
     void ProcessMouseInput(const std::shared_ptr<MouseEventData>& data);

 signals:
    void Preview(const std::shared_ptr<EventArgs>& args);
    void Finished(const std::shared_ptr<EventArgs>& args);

private:
    bool _IsFinished;
    Marker* _Marker;
    gp_Pnt _CurrentPoint;
};

#endif  // SRC_IACT_TOOLACTION_POINTACTION_H_
