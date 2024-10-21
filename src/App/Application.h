// Copyright [2024] SonCAD

#ifndef SRC_APP_APPLICATION_H_
#define SRC_APP_APPLICATION_H_

#include <QString>
#include <QApplication>
#include <QCoreApplication>

#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"
#include "App/AppContext.h"

#include "Pres/Commands/CommandManager.h"

#define coreApp (static_cast<Application*>(QCoreApplication::instance()))

class Application : public QApplication {
    Q_OBJECT

 public:
    Application(int& argc, char** argv);
    ~Application() {}

    CommandManager* commandManager() const {
        return mCommandManager;
    }

    AppContext* appContext() const {
        return mAppContext;
    }

    MainWindow* mainWindow() const {
        return mMainWindow;
    }

 private:
    void initTranslation();

 private:
    CommandManager* mCommandManager = new CommandManager;
    AppContext* mAppContext = new AppContext;

 private:
    WelcomeDialog* mWelcomeDialog = nullptr;
    MainWindow* mMainWindow = nullptr;
};

#endif  // SRC_APP_APPLICATION_H_
