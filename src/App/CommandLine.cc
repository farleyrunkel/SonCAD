// Copyright [2024] SonCAD

#include <iostream>
#include <string>

#include "App/CommandLine.h"

CommandLine::CommandLine(int argc, char* argv[]) {
    try {
        cxxopts::Options options(argv[0], " - Command line options");

        // Define options
        options.add_options()
            ("sandbox", "Enable sandbox", cxxopts::value<bool>(mEnableSandbox)->default_value("false"))
            ("nowelcome", "Disable welcome", cxxopts::value<bool>(mNoWelcomeDialog)->default_value("false"))
            ("runscript", "Script to run", cxxopts::value<std::string>(mScriptToRun))
            ("input", "Path to open", cxxopts::value<std::string>(mPathToOpen))
            ("help", "Show help");

        // Parse options
        auto result = options.parse(argc, argv);

        // Show help if requested
        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return;  // Use return instead of exit
        }

        // Set path if unmatched arguments exist
        if (!result.unmatched().empty()) {
            mPathToOpen = result.unmatched().at(0);
        }
    }
    catch (const cxxopts::exceptions::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;  // Use return instead of exit
    }
}
