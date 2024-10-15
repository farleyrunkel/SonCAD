// Copyright [2024] SonCAD

#ifndef APP_MAINWINDOW_H
#define APP_MAINWINDOW_H

#include "SARibbonMainWindow.h"

class MainWindow : public SARibbonMainWindow {
    Q_OBJECT

 public:
     explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

 private:
    void setupUi();
};

#endif  // APP_MAINWINDOW_H
