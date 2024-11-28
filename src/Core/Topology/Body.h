// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_BODY_H_
#define SRC_CORE_TOPOLOGY_BODY_H_

#include <QObject>

#include <gp.hxx>
#include <gp_Pnt.hxx>
#include <Standard_Transient.hxx>

#include "Core/Topology/InteractiveEntity.h"

class Sun_Shape;

DEFINE_STANDARD_HANDLE(Sun_Body, Standard_Transient)

class Sun_Body : public InteractiveEntity 
{
    Q_OBJECT

public:

    Sun_Body() {}


    bool AddShape(const Handle(Sun_Shape)& shape, bool saveUndo = true)
    {

        return true;
    }
    void SaveTopologyUndo() {}

    void SetPosition(const gp_Pnt& value) {
        if (!_Position.IsEqual(value, std::numeric_limits<double>::epsilon()))
        {
            SaveUndo();
            _Position = value;
            _InvalidateTransformation();
        }
    }

private:
    void _InvalidateTransformation() {}

private:
    gp_Pnt _Position = gp::Origin();
};


#endif  // SRC_CORE_TOPOLOGY_BODY_H_
