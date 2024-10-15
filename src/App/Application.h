// Copyright [2024] SonCAD

#ifndef APP_APPLICATION_H
#define APP_APPLICATION_H

#include <QString>
#include <QApplication>

#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"

#define coreApp (static_cast<Application*>(qApp))

class Application : public QApplication {
    Q_OBJECT

 public:
    Application(int& argc, char** argv);
    ~Application() = default;

    MainWindow* mainWindow(MainWindow* xMainWindow) const {
        return mMainWindow;
    }

 private:
    void initializeTranslation();

 private:
    MainWindow* mMainWindow = nullptr;
    WelcomeDialog* mWelcomeDialog = nullptr;
};

#endif  // APP_APPLICATION_H
