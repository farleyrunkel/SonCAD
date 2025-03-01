// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_MODEL_H_
#define CORE_TOPOLOGY_MODEL_H_

#include <QVector>
#include <boost/signals2.hpp>

#include <Standard_Handle.hxx>
#include "Core/Workspace.h"
#include "Comm/BaseObject.h"

DEFINE_STANDARD_HANDLE(Model, BaseObject)

class Model : public BaseObject
{
public:
    Model();

    QVector<Handle(Workspace)>& GetWorkspaces();

    static QString FileExtension();

    QString FilePath() const;

    bool Save() const;

    bool HasUnsavedChanges() const;

public:
    // Signals
    boost::signals2::signal<void()> OnResetUnsavedChanges;

private:
    QVector<Handle(Workspace)> _Workspaces;
};

#endif  // CORE_TOPOLOGY_MODEL_H_
