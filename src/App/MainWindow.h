// Copyright [2024] SunCAD

#ifndef SRC_APP_MAINWINDOW_H_
#define SRC_APP_MAINWINDOW_H_

#include <QWidget>

#include "SARibbonBar.h"
#include "SARibbonMainWindow.h"
#include "DockManager.h"

#include "App/Commands/AppCommands.h"

class MainWindow : public SARibbonMainWindow {
    Q_OBJECT

 public:
     explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

 private:
    void setupUi();
    void setupWelcomePage();
    void setupAppButton();
    void setupCategories();

    QAction* createAction(const QString& text, const QString& iconurl);

    void load();

 private:
    QMenu* myAppButton = nullptr;
    SARibbonBar* myRibbonBar = nullptr;;
    // The main container for docking
    ads::CDockManager* m_DockManager = nullptr;;
};

#endif  // SRC_APP_MAINWINDOW_H_
