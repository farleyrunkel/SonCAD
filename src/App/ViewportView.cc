// Copyright [2024] SunCAD

#include "App/ViewportView.h"

#include <QSpacerItem>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

#include "Iact/Viewport/ViewportPanel.h"

ViewportView::ViewportView(QWidget* parent)
    : QScrollArea(parent)
    , _ViewportPanel(nullptr)
{
    // Set layout for the main panel
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QFont font;
    font.setFamily("Arial");
    font.setPointSize(10);
    font.setBold(true);

    // Tool and error message area
    _MessageBar = new QLabel("Tool and error message area");
    _MessageBar->setContentsMargins(20, 2, 20, 2);
    _MessageBar->setFont(font);
    _MessageBar->setStyleSheet("background-color: lightyellow;");
    mainLayout->addWidget(_MessageBar);

    // Add spacer between the labels
    mainLayout->addStretch(1);

    // Grid information display
    QLabel* gridInfo = new QLabel("Grid information display area");
    gridInfo->setContentsMargins(_MessageBar->contentsMargins());
    gridInfo->setFont(_MessageBar->font());
    gridInfo->setStyleSheet(_MessageBar->styleSheet());
    mainLayout->addWidget(gridInfo);

    _ViewportPanel = new ViewportPanel(this);
    setWidget(_ViewportPanel);
    setWidgetResizable(true);
}
