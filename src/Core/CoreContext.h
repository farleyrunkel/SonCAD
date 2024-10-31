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
     CoreContext();;

 public:
    // Example method to save settings
    void saveSettings(const std::string& name) {
        // Implement saving logic here
    }
signals:
    void documentChanged(Model* document);
    void workspaceChanged(Workspace* workspace);
    void viewportChanged(Viewport* viewport);
 public:

    Model* document() const { return m_document; }
    Viewport* viewport() const { return m_viewport; }

    void setDocument(Model* document);

    virtual void setViewport(Viewport* viewport);

    virtual void setWorkspace(Workspace* workspace);

 protected:
    Workspace* m_workspace;
    Viewport* m_viewport;
    Model* m_document;
};

#endif  // SRC_CORE_CORECONTEXT_H_
