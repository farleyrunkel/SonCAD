// Copyright [2024] SunCAD

#include "Core/Topology/Model.h"

Model::Model()
{}

QVector<Handle(Workspace)>& Model::GetWorkspaces()
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
