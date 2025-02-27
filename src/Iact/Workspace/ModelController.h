// Copyright [2024] SunCAD

#ifndef IACT_WORKSPACE_MODELCONTROLLER_H_
#define IACT_WORKSPACE_MODELCONTROLLER_H_

#include "Comm/BaseObject.h"

#include <string>

    DEFINE_STANDARD_HANDLE(ModelController, BaseObject)

     class ModelController : public BaseObject
    {
    public:
        ModelController() {}
        ~ModelController() {}


        bool AskForSavingModelChanges() {
            return true;
        }

        void NewModel() {
        
        }

        void OpenModelFrom(const std::string& ) {}
    };

#endif // IACT_WORKSPACE_MODELCONTROLLER_H_
