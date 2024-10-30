// Copyright [2024] SunCAD

#include "App/ViewportView.h"

#include "Iact/Viewport/ViewportPanel.h"

ViewportView::ViewportView(QWidget* parent)
    : QScrollArea(parent)
{
    // Create main panel for the viewport
    QWidget* viewportPanel = new ViewportPanel();
    QVBoxLayout* mainLayout = new QVBoxLayout(viewportPanel);

    // Tool and error message area
    QLabel* messageBar = new QLabel("Tool and error message area");
    mainLayout->addWidget(messageBar);

    // Grid information display
    QLabel* gridInfo = new QLabel("Grid information display area");
    gridInfo->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(gridInfo);

    // Set layout for the main panel
    viewportPanel->setLayout(mainLayout);
    setWidget(viewportPanel); // Set as the scrollable area
    setWidgetResizable(true); // Allow resizing
}
