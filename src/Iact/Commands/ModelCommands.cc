// Copyright [2024] SunCAD

#include "Iact/Commands/ModelCommands.h"

#include <QIcon>
#include <QMessageBox>
#include <QObject>

#include "App/ResourceUtils.h"
#include "Iact/Commands/CommandHelper.h"
#include "Iact/Primitives/CreateBoxTool.h"

// Initialize the static command outside the class
ActionCommand& ModelCommands::CreateBox() 
{
    static ActionCommand command(
        []() { CommandHelper::StartTool(new CreateBoxTool()); },
        []() { return CommandHelper::CanStartTool(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Box"));
        command.setIcon(Resource::Icon("Model/Prim-Box"));
        command.setToolTip(QObject::tr("Creates a new body with a box shape."));
    }

    return command;
}

ActionCommand& ModelCommands::CreateCylinder()
{
    static ActionCommand command(
        []() {  },
        []() { return CommandHelper::CanStartTool(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Cylinder"));
        command.setIcon(Resource::Icon("Model/Prim-Cylinder"));
        command.setToolTip(QObject::tr("Creates a new body with a Cylinder shape."));
    }
    return command;
}

ActionCommand& ModelCommands::CreateSphere()
{
    static ActionCommand command(
        []() { },
        []() { return CommandHelper::CanStartTool(); }
    );

    // Initialize command properties if not already set
    if (command.text().isEmpty()) {
        command.setText(QObject::tr("Sphere"));
        command.setIcon(Resource::Icon("Model/Prim-Sphere"));
        command.setToolTip(QObject::tr("Creates a new body with a Sphere shape."));
    }
    return command;
}

ActionCommand& ModelCommands::CreateSketch()
{
    static ActionCommand command(
        []() {},
        []() { return CommandHelper::CanStartTool(); }
    );

    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Sketch"));
        command.setIcon(Resource::Icon("Model/Prim-Sketch"));
        command.setToolTip(QObject::tr("Creates a new body with a Sketch shape."));
    }
    return command;
}
