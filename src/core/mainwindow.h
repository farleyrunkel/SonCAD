// Copyright [2024] SonCAD

#ifndef SRC_CORE_MAINWINDOW_H_
#define SRC_CORE_MAINWINDOW_H_

#include "SARibbonMainWindow.h"
#include "SARibbonBar.h"

class MainWindow : public SARibbonMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};

#endif  // SRC_CORE_MAINWINDOW_H_
