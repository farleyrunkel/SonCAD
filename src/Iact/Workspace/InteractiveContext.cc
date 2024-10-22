// Copyright [2024] SunCAD

#include "Iact/Workspace/InteractiveContext.h"

InteractiveContext::~InteractiveContext() {
    if (_documentController) {
        _documentController->dispose();
        _documentController = nullptr;
    }
    if (_workspaceController) {
        _workspaceController->dispose();
        _workspaceController = nullptr;
    }
    _viewportController = nullptr;
}

// ModelController getter/setter

ModelController* InteractiveContext::documentController() const { return _documentController; }

void InteractiveContext::setDocumentController(ModelController* controller) {
    if (_documentController != controller) {
        if (_documentController) {
            _documentController->dispose();
        }
        _documentController = controller;
        emit documentControllerChanged();
    }
}

// WorkspaceController getter/setter

WorkspaceController* InteractiveContext::workspaceController() const { return _workspaceController; }

void InteractiveContext::setWorkspaceController(WorkspaceController* controller) {
    if (_workspaceController != controller) {
        if (_workspaceController) {
            _workspaceController->dispose();
        }
        _workspaceController = controller;
        emit workspaceControllerChanged();
    }
}

// ViewportController getter/setter

ViewportController* InteractiveContext::viewportController() const { return _viewportController; }

void InteractiveContext::setViewportController(ViewportController* controller) {
    if (_viewportController != controller) {
        _viewportController = controller;
        emit viewportControllerChanged();
    }
}

// RecentUsedColors getter

QList<QColor> InteractiveContext::recentUsedColors() const {
    return _recentUsedColors;
}

// RecentUsedScripts getter

QList<QString> InteractiveContext::recentUsedScripts() const {
    return _recentUsedScripts;
}

void InteractiveContext::addToScriptMruList(const QString& filePath) {
    int index = _recentUsedScripts.indexOf(filePath);
    if (index >= 0) {
        _recentUsedScripts.move(index, 0);
        _recentUsedScripts[0] = filePath;
    }
    else {
        if (_recentUsedScripts.size() >= _maxScriptMruCount) {
            _recentUsedScripts.removeLast();
        }
        _recentUsedScripts.prepend(filePath);
    }
    emit recentUsedScriptsChanged();
}
