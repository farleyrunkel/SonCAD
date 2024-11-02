// Copyright [2024] SunCAD

#include "App/ViewportView.h"

#include <QSpacerItem>
#include <QVBoxLayout>
#include <QLabel>

#include "Core/Core.h"
#include "Iact/Viewport/ViewportPanel.h"

ViewportView::ViewportView(QWidget* parent)
    : QScrollArea(parent) {
    // Create main panel for the viewport
    ViewportPanel* viewportPanel = new ViewportPanel();
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

    //connect(Core::appContext(), &AppContext::workspaceControllerChanged, viewportPanel, [viewportPanel] {
    //    viewportPanel->setWorkspaceController(Core::appContext()->workspaceController());
    //    });

    //connect(Core::appContext(), &AppContext::viewportControllerChanged, viewportPanel, [viewportPanel] {
    //    viewportPanel->setViewportController = Core::appContext()->viewportController(); });

    connect(Core::appContext(), &AppContext::workspaceChanged, viewportPanel, [viewportPanel](Workspace* workspace) {
        if (workspace) {
            viewportPanel->setViewer(workspace->v3dViewer());
            viewportPanel->setAisContext(workspace->aisContext());
        }
    });

    connect(Core::appContext(), &AppContext::viewportChanged, viewportPanel, [viewportPanel](Viewport* viewport) {
        if (viewport) {
            viewportPanel->setView(viewport->v3dView());
        }
    });
}
