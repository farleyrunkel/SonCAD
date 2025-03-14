// Copyright [2024] SunCAD

#include <QSystemSemaphore>
#include <QMessageBox>
#include <QLibrary>

#include "App/Application.h"
#include "Comm/Utils.h"

int main(int argc, char *argv[]) 
{
    Utils::RedirectOCCTMessagesToFile("E://Github//SonCAD//SunCAD.log");

    Application app(argc, argv);

    QSystemSemaphore sema(app.applicationName(), 1, QSystemSemaphore::Open);
    if (!sema.acquire()) {
        QMessageBox::warning(nullptr, "Error", "An instance of the application is already running.");
        return 1;
    }

    app.exec();

    sema.release();
    return 0;
}
