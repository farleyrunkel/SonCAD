// Copyright [2024] SunCAD

#include "App/ViewportView.h"

#include <QSpacerItem>
#include <QVBoxLayout>
#include <QLabel>

#include "Core/Core.h"
#include "Iact/Viewport/ViewportPanel.h"

ViewportView::ViewportView(QWidget* parent)
    : QScrollArea(parent),
    m_viewportPanel(nullptr) {

    // Set layout for the main panel
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

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

    connect(Core::appContext(), &AppContext::workspaceChanged, [this](Workspace* workspace) {
        if (workspace) {
            if (m_viewportPanel) {
                delete m_viewportPanel;
            }
            // Create main panel for the viewport
            m_viewportPanel = new ViewportPanel();
            m_viewportPanel->setViewer(workspace->v3dViewer());
            m_viewportPanel->setAisContext(workspace->aisContext());

            connect(Core::appContext(), &AppContext::viewportChanged, [this](Viewport* viewport) {
                if (viewport) {
                    m_viewportPanel->setView(viewport->v3dView());
                    setWidget(m_viewportPanel); // Set as the scrollable area
                    setWidgetResizable(true); // Allow resizing
                }}
            );

            connect(Core::appContext(), &AppContext::workspaceControllerChanged,
                m_viewportPanel, &ViewportPanel::setWorkspaceController);

            connect(Core::appContext(), &AppContext::viewportControllerChanged,
                m_viewportPanel, &ViewportPanel::setViewportController);
        }}
    );
}
