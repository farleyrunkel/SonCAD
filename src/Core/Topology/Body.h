// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_BODY_H_
#define CORE_TOPOLOGY_BODY_H_

#include <QObject>

#include <gp.hxx>
#include <gp_Pnt.hxx>
#include <Standard_Transient.hxx>
#include <gp_Quaternion.hxx>

#include "Comm/BaseObject.h"


    DEFINE_STANDARD_HANDLE(Body, Standard_Transient)

    class Body : public BaseObject
    {
    public:
        void SetPosition(const gp_Pnt& pnt) {}
    };


#endif  // CORE_TOPOLOGY_BODY_H_
