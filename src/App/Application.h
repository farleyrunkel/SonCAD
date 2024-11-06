// Copyright [2024] SunCAD

#ifndef SRC_APP_APPLICATION_H_
#define SRC_APP_APPLICATION_H_

#include <QString>
#include <QApplication>
#include <QCoreApplication>

#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"
#include "App/AppContext.h"

#include "Pres/Commands/CommandManager.h"

class Core;

class Application : public QApplication {
    Q_OBJECT

 public:
    Application(int& argc, char** argv);
    ~Application() {}

 private:
    void initTranslation();

 private:
    friend class Core;

    CommandManager* m_commandManager = nullptr;
    AppContext* m_appContext = nullptr;

 private:
    WelcomeDialog* mWelcomeDialog = nullptr;
    MainWindow* m_mainWindow = nullptr;
};

#endif  // SRC_APP_APPLICATION_H_
