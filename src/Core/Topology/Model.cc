// Copyright [2024] SunCAD

#include "Core/Topology/Model.h"

#include <NCollection_Vector.hxx>

Model::Model()
{
	Handle(Workspace) workspace = new Workspace(this);
    _Workspaces.Append(workspace);
}

NCollection_Vector<Handle(Workspace)>& Model::GetWorkspaces()
{
    return _Workspaces;
}

QString Model::FileExtension()
{
    return "step";
}

QString Model::FilePath() const
{
    return "";
}

bool Model::Save() const
{
    return false;
}

bool Model::HasUnsavedChanges() const
{
    return false;
}
