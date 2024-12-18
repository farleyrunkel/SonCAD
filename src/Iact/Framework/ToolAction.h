// Copyright [2024] SunCAD

#ifndef SRC_IACT_FRAMEWORK_TOOLACTION_H_
#define SRC_IACT_FRAMEWORK_TOOLACTION_H_

#include <QObject>
#include "Iact/Framework/WorkspaceControl.h"

class Sun_WorkspaceController;

class ToolAction : public WorkspaceControl {
    Q_OBJECT

 public:
    explicit ToolAction(QObject* parent = nullptr) {};

    // Start and stop functions
    bool start() { 
        return onStart(); 
    }
    virtual void reset() 
    {
        _IsFinished = false; 
    }
    void stop() 
    { 
        onStop();
        cleanup();
    }

    bool isFinished() const { return _IsFinished; }

 protected:
    // Virtual function for subclasses to override
    virtual bool onStart() { return false; }
    virtual void onStop() {}
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

#endif  // SRC_IACT_FRAMEWORK_TOOLACTION_H_
