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

    void OnMainWindowLoaded();

private:
    QMenu* _AppButton = nullptr;
    SARibbonBar* _RibbonBar = nullptr;
    // The main container for docking
    ads::CDockManager* _DockManager = nullptr;
};

#endif  // APP_MAINWINDOW_H_
