// Copyright [2024] SunCAD

#ifndef IACT_FRAMEWORK_TOOLACTION_H_
#define IACT_FRAMEWORK_TOOLACTION_H_

#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>

#include "Iact/Framework/WorkspaceControl.h"

DEFINE_STANDARD_HANDLE(ToolAction, WorkspaceControl);

class ToolAction : public WorkspaceControl
{
public:
    explicit ToolAction();;

    // Start and stop functions
    bool Start()
    {
        return OnStart();
    }

    void Stop();

    bool IsFinished() const
    {
        return _IsFinished;
    }

protected:
    // Virtual function for subclasses to override
    virtual bool OnStart()
    {
        return false;
    }
    virtual void OnStop()
    {}
    virtual void Reset()
    {
        _IsFinished = false;
    }

    //// Override from base class
    // bool onEntitySelectionChanging(const std::vector<InteractiveEntity*>& entitiesToSelect,
    //     const std::vector<InteractiveEntity*>& entitiesToUnSelect) override {
    //     return true;
    // }


protected:
    bool _IsFinished = false;
};

#endif  // IACT_FRAMEWORK_TOOLACTION_H_
