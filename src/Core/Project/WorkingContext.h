#ifndef SRC_CORE_PROJECT_WORKINGCONTEXT_H_
#define SRC_CORE_PROJECT_WORKINGCONTEXT_H_

#include <QObject>

#include "Core/Workspace.h"

#include <gp_Pln.hxx>
#include <gp.hxx>


class WorkingContext : public QObject 
{
    Q_OBJECT

public:
    explicit WorkingContext(QObject* parent = nullptr)
        : QObject(parent),
        _WorkingPlane(gp::XOY()),
        _GridType(Workspace::GridTypes::Rectangular),
        _GridStep(1.0),
        _GridRotation(0),
        _GridDivisions(8) {}

    // Getter ºÍ Setter ·½·¨
    gp_Pln workingPlane() const;
    void setWorkingPlane(const gp_Pln& plane);

    Workspace::GridTypes gridType() const;
    void setGridType(Workspace::GridTypes type);

    double gridStep() const;
    void setGridStep(double step);

    double gridRotation() const;
    void setGridRotation(double rotation);

    int gridDivisions() const;
    void setGridDivisions(int divisions);

private:
    gp_Pln _WorkingPlane;
    Workspace::GridTypes _GridType;
    double _GridStep;
    double _GridRotation;
    int _GridDivisions;
};

#endif  // SRC_CORE_PROJECT_WORKINGCONTEXT_H_
