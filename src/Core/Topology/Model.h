// Copyright [2024] SunCAD

#ifndef CORE_TOPOLOGY_MODEL_H_
#define CORE_TOPOLOGY_MODEL_H_

#include <QVector>
#include <boost/signals2.hpp>

#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>
#include <NCollection_Vector.hxx>

#include "Core/Workspace.h"
#include "Comm/BaseObject.h"

DEFINE_STANDARD_HANDLE(Model, BaseObject)

class Model : public TDocStd_Document
{
public:
    Model();

    NCollection_Vector<Handle(Workspace)>& GetWorkspaces();

    static QString FileExtension();

    QString FilePath() const;

    bool Save() const;

    bool HasUnsavedChanges() const;

public:
    // Signals
    boost::signals2::signal<void()> OnResetUnsavedChanges;

private:
    NCollection_Vector<Handle(Workspace)> _Workspaces;
};

#endif  // CORE_TOPOLOGY_MODEL_H_
