// Copyright [2024] SunCAD

#include "Iact/Workspace/ModelController.h"
#include "Core/Topology/Model.h"
#include "Core/Core.h"

ModelController::ModelController(QObject* parent) {}

void ModelController::dispose() {
}

Model* ModelController::newModel() {
    Model* newModel = new Model();
    Core::appContext()->setDocument(newModel);
    emit newModel->resetUnsavedChanges();
    return newModel;
}

bool ModelController::askForSavingModelChanges() { return true; }
