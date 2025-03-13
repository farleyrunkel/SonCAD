// Copyright [2024] SunCAD

// Own include
#include "Iact/Commands/ModelCommands.h"

#include "App/Resource.h"

ActionCommand& ModelCommands::createBox()
{
    static ActionCommand command;

    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Box"));
        command.setIcon(Resource::icon("Model/Prim-Box"));
        command.setToolTip(QObject::tr("Creates a new body with a box shape."));
    }

    return command;
}

ActionCommand& ModelCommands::createCylinder()
{
    static ActionCommand command;

    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Cylinder"));
        command.setIcon(Resource::icon("Model/Prim-Cylinder"));
        command.setToolTip(QObject::tr("Creates a new body with a Cylinder shape."));
    }
    return command;
}

ActionCommand& ModelCommands::createSphere()
{
    static ActionCommand command;
    // Initialize command properties if not already set
    if(command.text().isEmpty())
    {
        command.setText(QObject::tr("Sphere"));
        command.setIcon(Resource::icon("Model/Prim-Sphere"));
        command.setToolTip(QObject::tr("Creates a new body with a Sphere shape."));
    }
    return command;
}
