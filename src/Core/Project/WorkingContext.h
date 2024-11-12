// Copyright [2024] SunCAD

#ifndef SRC_CORE_PROJECT_WORKINGCONTEXT_H_
#define SRC_CORE_PROJECT_WORKINGCONTEXT_H_

#include <QObject>

#include "Core/Workspace.h"
#include "Occt/ValueTypes/Pln.h"

class WorkingContext : public QObject {
    Q_OBJECT

 public:
    explicit WorkingContext(QObject* parent = nullptr) {
        WorkingPlane = Pln::XOY();
        GridType = Workspace::GridTypes::Rectangular;
        GridStep = 1.0;
        GridRotation = 0;
        GridDivisions = 8;
    };

    gp_Pln WorkingPlane;
    Workspace::GridTypes GridType;
    double GridStep;
    double GridRotation;
    int GridDivisions;
};

#endif  // SRC_CORE_PROJECT_WORKINGCONTEXT_H_
