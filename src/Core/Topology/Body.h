// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_BODY_H_
#define SRC_CORE_TOPOLOGY_BODY_H_

#include <QObject>

#include <gp.hxx>
#include <gp_Pnt.hxx>
#include <Standard_Transient.hxx>

#include "Core/Topology/InteractiveEntity.h"

namespace Sun
{
    DEFINE_STANDARD_HANDLE(Body, Standard_Transient)

    class Body : public InteractiveEntity 
    {
        Q_OBJECT

    public:

        Body() {}


       void SetPosition(const gp_Pnt& value) {
           if (!_Position.IsEqual(value, std::numeric_limits<double>::epsilon()))
           {
               SaveUndo();
               _Position = value;
               _InvalidateTransformation();
               RaisePropertyChanged();
           }
       }

    private:
       void _InvalidateTransformation() {}

    private:
        gp_Pnt _Position = gp::Origin();
    };

} // namespace Sun

#endif  // SRC_CORE_TOPOLOGY_BODY_H_
