// Copyright [2024] SonCAD

#ifndef SRC_APP_APPCONTEXT_H_
#define SRC_APP_APPCONTEXT_H_

#include "Iact/Workspace/InteractiveContext.h"
#include "App/CommandLine.h"

class AppContext : public InteractiveContext {
 public:
    // Private constructor to prevent external instantiation
    AppContext() = default;

    // Private destructor to control instance destruction
    ~AppContext() = default;

    void initialize(CommandLine* cmdLine) {}
};

#endif  // SRC_APP_APPCONTEXT_H_
