// Copyright [2024] SunCAD

#ifndef SRC_CORE_CORECONTEXT_H_
#define SRC_CORE_CORECONTEXT_H_

#include <string>

#include <QObject>

#include "Comm/BaseObject.h"
#include "Core/Topology/Model.h"
#include "Core/Viewport.h"

// CoreContext class that follows the Singleton design pattern with lazy initialization
class CoreContext : public BaseObject {
    Q_OBJECT
    Q_PROPERTY(Model* document READ document WRITE setDocument)

 public:
    CoreContext() = default;

 public:
    // Example method to save settings
    void saveSettings(const std::string& name) {
        // Implement saving logic here
    }

 public:

     Model* document() const { return m_document; }

    void setDocument(Model* document) {
        m_document = document;
        emit propertyChanged("document");

        if (m_document && !m_document->workspaces().contains(m_workspace)) {
            Workspace* firstPrDefault = m_document->workspaces().empty()
                                        ? new Workspace()
                                        : m_document->workspaces().first();
            setWorkspace(firstPrDefault);
        }
    }

    void setViewport(Viewport* viewport) {
        m_viewport = viewport;
    }

    virtual void setWorkspace(Workspace* workspace) {
        m_workspace = workspace;
        if (m_workspace) {
            Viewport* firstPrDefault = m_workspace->viewports().empty() 
                                       ? new Viewport
                                       : m_workspace->viewports().first();
            setViewport(firstPrDefault);
        }      
    }

 protected:
    Workspace* m_workspace;
    Viewport* m_viewport;
    Model* m_document;
};

#endif  // SRC_CORE_CORECONTEXT_H_
