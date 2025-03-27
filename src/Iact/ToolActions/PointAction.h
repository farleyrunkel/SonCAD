// Copyright [2024] SunCAD

#ifndef IACT_TOOLACTION_POINTACTION_H_
#define IACT_TOOLACTION_POINTACTION_H_

#include <QMessageBox>

#include <boost/signals2.hpp>

#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>

#include "Iact/Visual/Marker.h"
#include "Iact/Framework/ToolAction.h"
#include "Iact/Workspace/MouseEventData.h"

class PointAction : public ToolAction
{
public:
    class EventArgs
    {
    public:
        EventArgs() {}
        EventArgs(const gp_Pnt& p, const gp_Pnt2d& pp, const gp_Pnt& mp, const std::shared_ptr < MouseEventData>& m)
            : Point(p), PointOnPlane(pp), MarkerPosition(mp), MouseEventData(m)
        {}
        gp_Pnt Point;
        gp_Pnt2d PointOnPlane;
        gp_Pnt MarkerPosition;
        std::shared_ptr<MouseEventData> MouseEventData;
    };

public:
    explicit PointAction();

public:
    boost::signals2::signal<void(std::shared_ptr<EventArgs>)> Preview;
    boost::signals2::signal<void(std::shared_ptr<EventArgs>)> Finished;

protected:
    bool OnStart() override;

    bool OnMouseMove(const std::shared_ptr<MouseEventData>& data) override;
    bool OnMouseDown(const std::shared_ptr<MouseEventData>& data) override;
    bool OnMouseUp(const std::shared_ptr<MouseEventData>& data) override;

private:
    void _EnsureMarker();
    void ProcessMouseInput(const std::shared_ptr<MouseEventData>& data);

private:
    Marker* _Marker;
    gp_Pnt _CurrentPoint;
};

#endif  // IACT_TOOLACTION_POINTACTION_H_
