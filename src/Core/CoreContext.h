// Copyright [2024] SunCAD

#ifndef CORE_CORECONTEXT_H
#define CORE_CORECONTEXT_H

#include <QObject>
#include <string>

#include "Comm/BaseObject.h"
#include "Core/Topology/Model.h"
#include "Core/Viewport.h"
#include "Core/Workspace.h"

// CoreContext class that follows the Singleton design pattern with lazy initialization
class CoreContext : public BaseObject
{
public:
    CoreContext();

public:
    Handle(Workspace) GetWorkspace();

    Handle(Viewport) GetViewport();

    virtual void SetDocument(const Handle(Model)& value);
    virtual void SetWorkspace(const Handle(Workspace)& value);
    virtual void SetViewport(const Handle(Viewport)& value);

    // Example method to save settings
    void SaveSettings(const std::string& Name)
    {
        // Implement saving logic here
    }

    static CoreContext* Current()
    {
        return _Current;
    }

private:
    Handle(Model)      _Document;
    Handle(Workspace)  _Workspace;
    Handle(Viewport)   _Viewport;

    static CoreContext* _Current;
};

#endif  // CORE_CORECONTEXT_H
