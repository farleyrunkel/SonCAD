// Copyright [2024] SonCAD

#ifndef SRC_APP_MAINWINDOW_H_
#define SRC_APP_MAINWINDOW_H_

#include <QWidget>

#include "SARibbonBar.h"
#include "SARibbonMainWindow.h"
#include "DockManager.h"

class MainWindow : public SARibbonMainWindow {
    Q_OBJECT

 public:
     explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

 private:
    void setupUi();

    void setupWelcomePage();

    void setupAppButton();
    QAction* createAction(const QString& text, const QString& iconurl);

    void setupCategories();

 private:
    QMenu* myAppButton = nullptr;
    SARibbonBar* myRibbonBar = nullptr;;
    // The main container for docking
    ads::CDockManager* m_DockManager = nullptr;;
};

#endif  // SRC_APP_MAINWINDOW_H_
