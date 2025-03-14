// Copyright [2024] SunCAD

#ifndef APP_APPLICATION_H
#define APP_APPLICATION_H

#include <memory>

#include <QString>
#include <QApplication>
#include <QCoreApplication>

#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"
#include "App/AppContext.h"

class Application : public QApplication 
{
    Q_OBJECT

public:
    Application(int& argc, char** argv);
    ~Application() {
        _MainWindow->deleteLater();
        _WelcomeDialog->deleteLater();
    }

    MainWindow* GetMainWindow() const
    {
        return _MainWindow;
    }

    AppContext* GetAppContext() const 
    {
        return _AppContext;
    }

private:
    void _InitializeTranslation();

private:
    MainWindow* _MainWindow = nullptr;
    WelcomeDialog* _WelcomeDialog = nullptr;
    AppContext* _AppContext= nullptr;
};

#define App static_cast<Application*>(QCoreApplication::instance())

#endif  // APP_APPLICATION_H
