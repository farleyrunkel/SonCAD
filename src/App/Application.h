// Copyright [2024] SonCAD

#ifndef APP_APPLICATION_H
#define APP_APPLICATION_H

#include <QString>
#include <QApplication>
#include <QSharedMemory>
#include <QSystemSemaphore>

#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"

#define coreApp (static_cast<Application*>(qApp))

class Application : public QApplication {
    Q_OBJECT

 public:
    Application(int& argc, char** argv);

    MainWindow* mainWindow(MainWindow* xMainWindow) {
        return mMainWindow;
    }

 private:
    void initializeTranslation();
    // Initialize the mutex and handle synchronization
    void initializeSynchronization();

 private:
    // Mutex name for instance protection
    const QString mMutexName = "MacadInstanceRunning";

    // Shared memory and semaphore for inter-process synchronization
    QSharedMemory mSharedMemory;
    QSystemSemaphore mSystemSemaphore;


 private:
    MainWindow* mMainWindow = nullptr;
    WelcomeDialog* mWelcomeDialog = nullptr;
};

#endif  // APP_APPLICATION_H
