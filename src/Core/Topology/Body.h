// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_BODY_H_
#define SRC_CORE_TOPOLOGY_BODY_H_

#include <QObject>

#include <gp.hxx>
#include <gp_Pnt.hxx>
#include <Standard_Transient.hxx>
#include <gp_Quaternion.hxx>

#include "Core/Topology/InteractiveEntity.h"
#include "Core/Core.h"
#include "Core/Topology/Layer.h"

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

    gp_Pnt Position() const {
        return _Position;
    }

    void SetPosition(const gp_Pnt& value) {
        if (!_Position.IsEqual(value, std::numeric_limits<double>::epsilon()))
        {
            SaveUndo();
            _Position = value;
            _InvalidateTransformation();
        }
    }

    Handle(Sun_Layer) Layer() const {
        return Handle(Sun_Layer)();
    }

    void SetLayer(const Sun_Layer& value) {
    }

    gp_Quaternion Rotation() const {
        return _Quaternion;
    }

    void SetRotation(const gp_Quaternion& value) {
        if (!_Quaternion.IsEqual(value))
        {
            SaveUndo();
            _Quaternion = value;
            _InvalidateTransformation();
        }
    }

    static Handle(Sun_Body) Create(const Handle(Sun_Shape)& shape)
    {
        Handle(Sun_Body) body = new Sun_Body;
        //body->SetName(""); //  CoreContext.Current.Document ? .AddNextNameSuffix(shape.Name) ? ? shape.Name,
        //body->SetLayer(Core::appContext()->Layers()->ActiveLayer());
        //    //body->SetDocument = CoreContext.Current.Document
        body->AddShape(shape, false);

        return body;
    }

private:
    void _InvalidateTransformation() {}

private:
    gp_Pnt _Position = gp::Origin();
    gp_Quaternion _Quaternion;
};


#endif  // SRC_CORE_TOPOLOGY_BODY_H_
