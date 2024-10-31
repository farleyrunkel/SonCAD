// Copyright [2024] SunCAD

#include "Iact/Workspace/InteractiveContext.h"

InteractiveContext::InteractiveContext() : CoreContext(),
    m_documentController(new ModelController(this)),
    m_viewportController(nullptr),
    m_workspaceController(nullptr) {
    initialize();
}

InteractiveContext::~InteractiveContext() {
    if (m_documentController) {
        m_documentController->dispose();
        m_documentController = nullptr;
    }
    if (m_workspaceController) {
        m_workspaceController->dispose();
        m_workspaceController = nullptr;
    }
    m_viewportController = nullptr;
}

// ModelController getter/setter

ModelController* InteractiveContext::documentController() const { return m_documentController; }

void InteractiveContext::setDocumentController(ModelController* controller) {
    if (m_documentController != controller) {
        if (m_documentController) {
            m_documentController->dispose();
        }
        m_documentController = controller;

        emit propertyChanged("documentController");
    }
}

// WorkspaceController getter/setter

WorkspaceController* InteractiveContext::workspaceController() const { return m_workspaceController; }

void InteractiveContext::setWorkspaceController(WorkspaceController* controller) {
    if (m_workspaceController != controller) {
        if (m_workspaceController) {
            m_workspaceController->dispose();
        }
        m_workspaceController = controller;

        emit propertyChanged("workspaceController");
    }
}

// ViewportController getter/setter

ViewportController* InteractiveContext::viewportController() const { return m_viewportController; }

void InteractiveContext::setViewportController(ViewportController* controller) {
    if (m_viewportController != controller) {
        m_viewportController = controller;

        emit propertyChanged("viewportController");
    }
}

void InteractiveContext::setWorkspace(Workspace* workspace) {
    if (m_workspace == workspace) {
        return;
    }
    CoreContext::setWorkspace(workspace);

    if (workspace) {
        setWorkspaceController(new WorkspaceController(workspace));
    }
}

void InteractiveContext::setViewport(Viewport* viewport) {
    if (m_viewport == viewport) {
        return;
    }
    CoreContext::setViewport(viewport);

    if (viewport == nullptr) {
        setViewportController(nullptr);
        if (workspaceController()) {
            workspaceController()->setActiveViewport(nullptr);
        }
        else {
            workspaceController()->setActiveViewport(CoreContext::viewport());
            setViewportController(workspaceController()->viewportController(CoreContext::viewport()));
        }
    }
}

// RecentUsedColors getter

QList<QColor> InteractiveContext::recentUsedColors() const {
    return m_recentUsedColors;
}

// RecentUsedScripts getter

QList<QString> InteractiveContext::recentUsedScripts() const {
    return m_recentUsedScripts;
}

void InteractiveContext::addToScriptMruList(const QString& filePath) {
    int index = m_recentUsedScripts.indexOf(filePath);
    if (index >= 0) {
        m_recentUsedScripts.move(index, 0);
        m_recentUsedScripts[0] = filePath;
    }
    else {
        if (m_recentUsedScripts.size() >= m_maxScriptMruCount) {
            m_recentUsedScripts.removeLast();
        }
        m_recentUsedScripts.prepend(filePath);
    }

    emit propertyChanged("recentUsedScripts");
}

void InteractiveContext::initialize() {
    connect(this, &InteractiveContext::workspaceControllerChanged, [this]() {emit propertyChanged("workspaceController"); });
    connect(this, &InteractiveContext::documentControllerChanged, [this]() {emit propertyChanged("documentController"); });
    connect(this, &InteractiveContext::viewportControllerChanged, [this]() {emit propertyChanged("viewportController"); });
}
