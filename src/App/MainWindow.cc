// Copyright [2024] SonCAD

#include "App/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : SARibbonMainWindow(parent)
{
	setupUi();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    this->resize(800, 600);
    this->setWindowTitle(tr("Main Window"));
}
