// Copyright [2024] SunCAD

#ifndef APP_APPLICATION_H
#define APP_APPLICATION_H

#include <memory>

#include <QString>
#include <QApplication>

#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"
#include "App/AppContext.h"

#define App static_cast<Application*>(qApp)

class Application : public QApplication 
{
    Q_OBJECT

public:
    Application(int& argc, char** argv);
    ~Application() {
        _MainWindow->deleteLater();
        _WelcomeDialog->deleteLater();
    }

	MainWindow* GetMainWindow() const noexcept
    {
        return _MainWindow;
    }

    AppContext* GetAppContext() const noexcept
    {
        return _AppContext;
    }

private:
    void _InitializeTranslation();

private:
    MainWindow* _MainWindow;
    WelcomeDialog* _WelcomeDialog;
    AppContext* _AppContext;
};

#endif  // APP_APPLICATION_H
