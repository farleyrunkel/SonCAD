// Copyright [2024] SunCAD

#ifndef APP_APPCONTEXT_H
#define APP_APPCONTEXT_H

#include "App/CommandLine.h"
#include "Iact/Workspace/InteractiveContext.h"

// AppContext
DEFINE_STANDARD_HANDLE(AppContext, InteractiveContext)

class AppContext : public InteractiveContext
{
public:
    // Private constructor to prevent external instantiation
    AppContext()
    {}

    // Private destructor to control instance destruction
    ~AppContext()
    {};

    void Initialize(const CommandLine& cmdLine)
    {}
};

#endif  // APP_APPCONTEXT_H
