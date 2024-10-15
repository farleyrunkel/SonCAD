// Copyright [2024] SonCAD

#ifndef APP_COMMANDLINE_H
#define APP_COMMANDLINE_H

#include <iostream>
#include <string>

#include <cxxopts.hpp>

class CommandLine {
 public:
    CommandLine(int argc, char* argv[]);

    bool hasPathToOpen() const { return !mPathToOpen.empty(); }
    bool hasScriptToRun() const { return !mScriptToRun.empty(); }
    bool isSandboxEnabled() const { return mEnableSandbox; }
    bool isWelcomeDialogDisabled() const { return mNoWelcomeDialog; }

 private:
    std::string mPathToOpen;          // Path to open
    bool mEnableSandbox = false;      // Sandbox mode
    bool mNoWelcomeDialog = false;    // Welcome status
    std::string mScriptToRun;         // Script to run
};

#endif // APP_COMMANDLINE_H
