// Copyright [2024] SonCAD

#include "App/MainWindow.h"

#include <QAction>
#include <QLabel>
#include <QStatusBar>
#include <QScopedPointer>
#include <QAbstractButton>

#include "SARibbonBar.h"
#include "SARibbonApplicationButton.h"
#include "SARibbonMenu.h"

#include "App/WelcomeDialog.h"
#include "Iact/Commands/ModelCommands.h"

MainWindow::MainWindow(QWidget *parent)
    : SARibbonMainWindow(parent) {
	setupUi();
    setupWelcomePage();

    setupAppButton();
    setupCategories();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    resize(1260, 800);

    setWindowTitle(tr("SonCAD"));
    setStatusBar(new QStatusBar());

    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::XmlCompressionEnabled, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
    m_DockManager = new ads::CDockManager(this);

    // set ribbonbar
    myRibbonBar = ribbonBar();
    myRibbonBar->setContentsMargins(5, 0, 5, 0);
}

void MainWindow::setupWelcomePage() {
    WelcomeDialog* l = new WelcomeDialog();

    // Create a dock widget with the title Label 1 and set the created label
    // as the dock widget content
    ads::CDockWidget* DockWidget = new ads::CDockWidget("Welcome");
    DockWidget->setWidget(l);

    // Add the dock widget to the top dock widget area
    m_DockManager->addDockWidget(ads::TopDockWidgetArea, DockWidget);
}

void MainWindow::setupAppButton() {
    if (!myRibbonBar) {
        return;
    }
    QAbstractButton* btn = myRibbonBar->applicationButton();
    if (!btn) {
        btn = new SARibbonApplicationButton(this);
        myRibbonBar->setApplicationButton(btn);
    }
    myRibbonBar->applicationButton()->setText(("  &File  "));

    if (!myAppButton) {
        myAppButton = new SARibbonMenu(this);
        myAppButton->addAction(createAction("test1", "://icon/action.svg"));
        myAppButton->addAction(createAction("test2", "://icon/action2.svg"));
    }
    SARibbonApplicationButton* appBtn = qobject_cast<SARibbonApplicationButton*>(btn);
    if (!appBtn) {
        return;
    }
    appBtn->setMenu(myAppButton);
}

void MainWindow::setupCategories() {
    if (SARibbonCategory* aCategory = myRibbonBar->addCategoryPage(tr("Edit"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Panel 1"))) {
            QAction* aAction = new QAction;
            aAction->setText("save");
            aAction->setIcon(QIcon("://icon/save.svg"));
            aAction->setObjectName("actSave");
            aAction->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));
            aPannel->addLargeAction(aAction);
        }
    }

    if (SARibbonCategory* aCategory = myRibbonBar->addCategoryPage(tr("Model"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Create"))) {
            aPannel->addAction(&ModelCommands::CreateBox(), SARibbonPannelItem::Large);
            aPannel->addAction(new QAction(QIcon("://icons/model/Prim-Cylinder.svg"), "Cylinder"), SARibbonPannelItem::Large);
            aPannel->addAction(new QAction(QIcon("://icons/model/Prim-Sphere.svg"), "Sphere"), SARibbonPannelItem::Large);
        }
    }

    if (SARibbonCategory* aCategory = myRibbonBar->addCategoryPage(tr("View"))) {
        if (SARibbonPannel* aPannel = aCategory->addPannel(tr("Widgets"))) {
            aPannel->addAction(&ModelCommands::CreateBox(), SARibbonPannelItem::Large);
        }
    }
}

QAction* MainWindow::createAction(const QString& text, const QString& iconurl) {
    QAction* act = new QAction(this);
    act->setText(text);
    act->setIcon(QIcon(iconurl));
    act->setObjectName(text);
    return act;
}
