// Copyright [2024] SunCAD

#ifndef APP_MAINWINDOW_H_
#define APP_MAINWINDOW_H_

#include <QWidget>

#include "SARibbonBar.h"
#include "SARibbonMainWindow.h"
#include "DockManager.h"

#include "App/Commands/AppCommands.h"

class MainWindow : public SARibbonMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    void SetupUi();
    void SetupDockWidgets();
    void SetupAppButton();
    void SetupCategories();

private:
    void _MainWindow_Loaded();

private:
    QMenu* _AppButton;
    SARibbonBar* _RibbonBar;
    ads::CDockManager* _DockManager;     // The main container for docking
};

#endif  // APP_MAINWINDOW_H_
