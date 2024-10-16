// Copyright [2024] SonCAD

#ifndef CORE_CORECONTEXT_H
#define CORE_CORECONTEXT_H

#include <string>

#include <QObject>

// CoreContext class that follows the Singleton design pattern with lazy initialization
class CoreContext : public QObject {
    Q_OBJECT

 public:
    // Static method to get the single instance of CoreContext with lazy initialization
    static CoreContext* instance() {
        static CoreContext instance; // Guaranteed to be destroyed, instantiated on first use
        return &instance;
    }

    // Example method to save settings
    void saveSettings(const std::string& name) {
        // Implement saving logic here
    }

 private:
    // Private constructor to prevent external instantiation
    CoreContext() = default;

    // Private destructor to control instance destruction
    virtual ~CoreContext() = default;

    // Copy constructor and assignment operator are deleted to prevent copying
    CoreContext(const CoreContext&) = delete;
    CoreContext& operator=(const CoreContext&) = delete;
};

#endif  // CORE_CORECONTEXT_H
