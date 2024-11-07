// Copyright [2024] SunCAD

#include "Iact/Workspace/ModelController.h"

#include <QFileDialog>
#include <QElapsedTimer>

#include "Core/Core.h"
#include "Core/Topology/Model.h"

ModelController::ModelController(QObject* parent) {}

Model* ModelController::newModel() {
    Model* newModel = new Model();
    Core::appContext()->setDocument(newModel);
    emit newModel->resetUnsavedChanges();
    return newModel;
}

bool ModelController::openModelFrom(const QString& initialDirectory) {
    // create and open file dialog;
    QFileDialog dlg;
    dlg.setWindowTitle("Open Model...");
    dlg.setFileMode(QFileDialog::ExistingFile);
    dlg.setNameFilter("SunCAD Models (*." + Model::fileExtension() + ")");
    dlg.setDefaultSuffix(Model::fileExtension());
    dlg.setDirectory(initialDirectory.isEmpty() ? QString() : initialDirectory);

    QString filePath;
    if (dlg.exec() == QDialog::Accepted) {
        filePath = dlg.selectedFiles().first();
    }

    // if no file return false
    if (filePath.isEmpty()) {
        return false;
    }

    // open selected
    return openModel(filePath);
}

bool ModelController::openModel(const QString& file) {
    return false;
}

bool ModelController::saveModel() {
    auto model = Core::appContext()->document();
    if (model->filePath().isEmpty()) {
        return saveModelAs();
    }
    else {
        if (model->save()) {
            return true;
        }
    }
    return false;
}

bool ModelController::saveModelAs() {
    return false;
}

bool ModelController::askForSavingModelChanges() { 
    return true; 
}

void ModelController::dispose() {
}
