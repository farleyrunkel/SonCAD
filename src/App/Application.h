// Copyright [2024] SunCAD

#ifndef APP_APPLICATION_H_
#define APP_APPLICATION_H_

#include <QString>

#include <QApplication>
#include <QMainWindow>

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int& argc, char** argv) : QApplication(argc, argv)
    {
        myMainWindow = new QMainWindow;
        myMainWindow->show();

    }
    virtual ~Application()
    {}

private:
    QMainWindow* myMainWindow;
};

#endif  // APP_APPLICATION_H_
