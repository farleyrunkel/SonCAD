// Copyright [2024] SonCAD

#ifndef SRC_CORE_APPLICATION_H_
#define SRC_CORE_APPLICATION_H_

#include <QString>
#include <QApplication>
#include <QSharedMemory>
#include <QSemaphore>

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
    // Mutex name for instance protection
    const QString mMutexName = "MacadInstanceRunning"; // »¥³âÃû

    // Shared memory and semaphore for inter-process synchronization
    QSharedMemory mSharedMemory;
    QSemaphore mSemaphore;

    // Initialize the mutex and handle synchronization
    void InitializeSynchronization();

 private:
    MainWindow* mMainWindow = nullptr;
    WelcomeDialog* mWelcomeDialog = nullptr;
};

#endif  // SRC_CORE_APPLICATION_H_
