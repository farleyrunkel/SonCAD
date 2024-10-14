// Copyright [2024] SonCAD

#include "core/mainwindow.h"
#include "core/Application.h"

int main(int argc, char *argv[]) {
    Application a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
