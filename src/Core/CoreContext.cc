// Copyright [2024] SunCAD

#include "Core/CoreContext.h"

CoreContext::CoreContext() {}

void CoreContext::setDocument(Model* document) {
    if (document == m_document) {
        return;
    }
    m_document = document;
    emit documentChanged(document);

    if (m_document && !m_document->workspaces().contains(m_workspace)) {
        Workspace* firstPrDefault = (m_document->workspaces().empty()
            ? new Workspace()
            : m_document->workspaces().first());
        setWorkspace(firstPrDefault);
    }
}

void CoreContext::setViewport(Viewport* viewport) {
    if (m_viewport != viewport) {
        m_viewport = viewport;
        emit viewportChanged(viewport);
    }
}

void CoreContext::setWorkspace(Workspace* workspace) {
    if (m_workspace == workspace) {
        return;
    }
    m_workspace = workspace;
    emit workspaceChanged(workspace);

    if (m_workspace) {
        Viewport* firstPrDefault = (m_workspace->viewports().empty()
            ? new Viewport()
            : m_workspace->viewports().first());
        setViewport(firstPrDefault);
    }
}
