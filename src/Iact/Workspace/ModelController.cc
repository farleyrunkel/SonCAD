// Copyright [2024] SunCAD

// Own include
#include "Iact/Workspace/ModelController.h"

#include "Core/Topology/Model.h"
#include "Iact/Workspace/InteractiveContext.h"

ModelController::ModelController()
{}

Handle(Model) ModelController::NewModel()
{
	Handle(Model) newModel = new Model();
	InteractiveContext::Current()->SetDocument(newModel);
	return newModel;
}
