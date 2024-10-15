// Copyright [2024] SonCAD

#include <QSystemSemaphore>
#include <QMessageBox>

#include "App/Application.h"

int main(int argc, char *argv[]) {
    Application a(argc, argv);

    QSystemSemaphore semaphore(a.applicationName(), 1, QSystemSemaphore::Open);
    if (!semaphore.acquire()) {
        QMessageBox::warning(nullptr, "Error", "An instance of the application is already running.");
        return 1;
    }

    a.exec();

    semaphore.release();
    return 0;
}
