// Copyright [2024] SunCAD

#include "Iact/Workspace/ModelController.h"

ModelController::ModelController(QObject* parent) {}

void ModelController::dispose() {
}

void ModelController::newModel() {
    //Model newModel = new();
    //InteractiveContext.Current.Document = newModel;
    //newModel.ResetUnsavedChanges();
    //return newModel;
}

bool ModelController::askForSavingModelChanges() { return true; }
