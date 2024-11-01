// Copyright [2024] SunCAD

#include "App/ViewportView.h"

#include <QSpacerItem>
#include <QVBoxLayout>
#include <QLabel>

#include "Iact/Viewport/ViewportPanel.h"

ViewportView::ViewportView(QWidget* parent)
    : QScrollArea(parent) {
    // Create main panel for the viewport
    QWidget* viewportPanel = new ViewportPanel();
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Tool and error message area
    QLabel* messageBar = new QLabel("Tool and error message area");
    messageBar->setStyleSheet("background-color: lightyellow;");
    mainLayout->addWidget(messageBar);

    // Add spacer between the labels
    mainLayout->addStretch(1);

    // Grid information display
    QLabel* gridInfo = new QLabel("Grid information display area");
    gridInfo->setStyleSheet("background-color: lightyellow;");
    mainLayout->addWidget(gridInfo);

    // Set layout for the main panel
    setLayout(mainLayout);
    setWidget(viewportPanel); // Set as the scrollable area
    setWidgetResizable(true); // Allow resizing
}
