// Copyright [2024] SunCAD

#ifndef APP_MAINWINDOW_H_
#define APP_MAINWINDOW_H_

#include <QWidget>
#include <QString>

#include "SARibbonBar.h"
#include "SARibbonMainWindow.h"

#include "DockManager.h"

class MainWindow : public SARibbonMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    void setupUi();
    void setupDockWidgets();
    void setupAppButton();
    void setupCategories();

    QAction* createAction(const QString& text, const QString& iconurl);

    void onMainWindowLoaded();

private:
    QMenu* m_appButton = nullptr;
    SARibbonBar* m_ribbonBar = nullptr;
    // The main container for docking
    ads::CDockManager* m_dockManager = nullptr;
};

#endif  // APP_MAINWINDOW_H_
