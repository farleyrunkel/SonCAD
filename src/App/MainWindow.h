// Copyright [2024] SonCAD

#ifndef SRC_CORE_MAINWINDOW_H_
#define SRC_CORE_MAINWINDOW_H_

#include "SARibbonMainWindow.h"

class MainWindow : public SARibbonMainWindow {
    Q_OBJECT

 public:
     explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    void setupUi();

private:

};

#endif  // SRC_CORE_MAINWINDOW_H_
