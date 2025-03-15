// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_MODELCONTROLLER_H_
#define IACT_WORKSPACE_MODELCONTROLLER_H_

#include <string>

#include "Comm/BaseObject.h"
#include "Core/Topology/Model.h"

DEFINE_STANDARD_HANDLE(ModelController, BaseObject)

class ModelController : public BaseObject
{
public:
    ModelController();
    ~ModelController()
    {}


    bool AskForSavingModelChanges()
    {
        return true;
    }

    Handle(Model) NewModel();

    void OpenModelFrom(const std::string&)
    {}
};

#endif // IACT_WORKSPACE_MODELCONTROLLER_H_
