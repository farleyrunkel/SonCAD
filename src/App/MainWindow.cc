// Copyright [2024] SunCAD

#include "App/MainWindow.h"

#include <QAbstractButton>
#include <QAction>
#include <QLabel>
#include <QPlainTextEdit>
#include <QScopedPointer>
#include <QStatusBar>

#include "SARibbonApplicationButton.h"
#include "SARibbonBar.h"
#include "SARibbonMenu.h"

#include "AutoHideDockContainer.h"
#include "DockAreaTitleBar.h"
#include "DockAreaWidget.h"

#include "Resource.h"

MainWindow::MainWindow(QWidget* parent)
    : SARibbonMainWindow(parent)
{
    setupUi();

    setupAppButton();
    setupCategories();

    setupDockWidgets();

    onMainWindowLoaded();
}

MainWindow::~MainWindow()
{}

void MainWindow::setupUi()
{
    resize(1260, 800);

    setWindowTitle(tr("SunCAD"));
    setWindowIcon(Resource::icon("App/App-MainLogo"));
    setStatusBar(new QStatusBar());

    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::AlwaysShowTabs, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::ActiveTabHasCloseButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::XmlCompressionEnabled, false);

    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasCloseButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasUndockButton, false);
    ads::CDockManager::setAutoHideConfigFlags(ads::CDockManager::DefaultAutoHideConfig);
    ads::CDockManager::setAutoHideConfigFlag(ads::CDockManager::DockAreaHasAutoHideButton, false);

    m_dockManager = new ads::CDockManager(this);

    // set ribbonbar
    m_ribbonBar = ribbonBar();
    m_ribbonBar->setContentsMargins(5, 0, 5, 0);
}

void MainWindow::setupAppButton()
{
    if (!m_ribbonBar) {
        return;
    }
    QAbstractButton* btn = m_ribbonBar->applicationButton();
    if (!btn) {
        btn = new SARibbonApplicationButton(this);
        m_ribbonBar->setApplicationButton(btn);
    }
    m_ribbonBar->applicationButton()->setText(tr("  &File  "));

    if (!m_appButton) {
        m_appButton = new SARibbonMenu(this);
        m_appButton->addAction(new QAction);
        m_appButton->addAction(new QAction);
        m_appButton->addSeparator();
        m_appButton->addAction(new QAction);
        m_appButton->addSeparator();
        m_appButton->addAction(new QAction);
        m_appButton->addSeparator();
        m_appButton->addAction(new QAction);
    }
    SARibbonApplicationButton* appBtn = qobject_cast<SARibbonApplicationButton*>(btn);
    if (!appBtn) {
        return;
    }
    appBtn->setMenu(m_appButton);
}

void MainWindow::setupCategories()
{
    if (SARibbonCategory* aCategory = m_ribbonBar->addCategoryPage(tr("Edit"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Undo"))) {
            aPannel->addAction(new QAction, SARibbonPannelItem::Large);
            aPannel->addAction(new QAction, SARibbonPannelItem::Large);
        }
    }

    if (SARibbonCategory* aCategory = m_ribbonBar->addCategoryPage(tr("Model"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Create"))) {
            aPannel->addAction(new QAction, SARibbonPannelItem::Large);
            aPannel->addAction(new QAction, SARibbonPannelItem::Large);
            aPannel->addAction(new QAction, SARibbonPannelItem::Large);
        }
    }

    if (SARibbonCategory* aCategory = m_ribbonBar->addCategoryPage(tr("ToolBox"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Convert"))) {
            aPannel->addAction(new QAction);
        }
    }

    if (SARibbonCategory* aCategory = m_ribbonBar->addCategoryPage(tr("View"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("View"))) {
            aPannel->addAction(new QAction);
            aPannel->addAction(new QAction);
            aPannel->addAction(new QAction);
            aPannel->addAction(new QAction);
            aPannel->addAction(new QAction);
            aPannel->addAction(new QAction);
        }
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Zoom"))) {
            aPannel->addAction(new QAction);
            aPannel->addAction(new QAction);
            aPannel->addAction(new QAction);
        }
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Display"))) {
        }
    }
}

void MainWindow::setupDockWidgets()
{
    // Set up a central dock widget 
    ads::CDockWidget* CentralDockWidget = new ads::CDockWidget("Workspace");
    CentralDockWidget->setWidget(new QWidget());
    auto* CentralDockArea = m_dockManager->setCentralWidget(CentralDockWidget);

    // Set up additional dock widgets for various panels
    ads::CDockWidget* documentDock = new ads::CDockWidget("Document");
    documentDock->setWidget(new QWidget());

    ads::CDockWidget* layersDock = new ads::CDockWidget("Layers");
    layersDock->setWidget(new QWidget());

    ads::CDockWidget* propertiesDock = new ads::CDockWidget("Properties");
    propertiesDock->setWidget(new QWidget());

    ads::CDockWidget* messageDock = new ads::CDockWidget("Message");
    messageDock->setWidget(new QWidget());

    // add dock widgets to specific dock areas
    m_dockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarRight, propertiesDock)->setSize(240);
    m_dockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarLeft, documentDock)->setSize(240);
    m_dockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarLeft, layersDock)->setSize(240);
    m_dockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarBottom, messageDock)->setSize(240);
}

void MainWindow::onMainWindowLoaded()
{
}

QAction* MainWindow::createAction(const QString& text, const QString& iconurl)
{
    QAction* action = new QAction(this);
    action->setText(text);
    action->setIcon(QIcon(iconurl));
    action->setObjectName(text);
    return action;
}
