// Copyright [2024] SonCAD

#ifndef SRC_CORE_CORECONTEXT_H_
#define SRC_CORE_CORECONTEXT_H_

#include <string>

#include <QObject>

// CoreContext class that follows the Singleton design pattern with lazy initialization
class CoreContext : public QObject {
    Q_OBJECT

 public:
    CoreContext() = default;

 public:
    // Example method to save settings
    void saveSettings(const std::string& name) {
        // Implement saving logic here
    }
};

#endif  // SRC_CORE_CORECONTEXT_H_
