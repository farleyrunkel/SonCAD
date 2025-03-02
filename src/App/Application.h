// Copyright [2024] SunCAD

#ifndef APP_APPLICATION_H_
#define APP_APPLICATION_H_

#include <QString>

#include <QApplication>
#include "App/MainWindow.h"

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int& argc, char** argv) : QApplication(argc, argv)
    {
        myMainWindow = new MainWindow;
        myMainWindow->show();

    }
    virtual ~Application()
    {}

private:
    MainWindow* myMainWindow;
};

#endif  // APP_APPLICATION_H_
