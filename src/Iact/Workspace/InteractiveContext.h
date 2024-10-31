// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_INTERACTIVECONTEXT_H_
#define SRC_IACT_WORKSPACE_INTERACTIVECONTEXT_H_

#include <QObject>
#include <QList>
#include <QString>
#include <QColor>
#include <QScopedPointer>
#include <QSharedPointer>

#include "Core/CoreContext.h"
#include "Core/Viewport.h"
#include "Comm/BaseObject.h"
#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Workspace/ModelController.h"
#include "Iact/Workspace/ViewportController.h"

class InteractiveContext : public CoreContext {
    Q_OBJECT
    Q_PROPERTY(ModelController* documentController READ documentController WRITE setDocumentController)
    Q_PROPERTY(WorkspaceController* workspaceController READ workspaceController WRITE setWorkspaceController)
    Q_PROPERTY(ViewportController* viewportController READ viewportController WRITE setViewportController)

 public:
    InteractiveContext();
    ~InteractiveContext() override;

    // ModelController getter/setter
    ModelController* documentController() const;
    void setDocumentController(ModelController* controller);

    // WorkspaceController getter/setter
    WorkspaceController* workspaceController() const;
    void setWorkspaceController(WorkspaceController* controller);

    // ViewportController getter/setter
    ViewportController* viewportController() const;
    void setViewportController(ViewportController* controller);

    void setWorkspace(Workspace* workspace) override;

    // RecentUsedColors getter
    QList<QColor> recentUsedColors() const;

    // RecentUsedScripts getter
    QList<QString> recentUsedScripts() const;

    void addToScriptMruList(const QString& filePath);

 private:
     void initialize();

 signals:
    void workspaceControllerChanged();
    void documentControllerChanged();
    void viewportControllerChanged();

 private:
    ModelController* m_documentController;
    WorkspaceController* m_workspaceController;
    ViewportController* m_viewportController;

    QList<QColor> m_recentUsedColors;
    QList<QString> m_recentUsedScripts;
    const int m_maxScriptMruCount = 10;
};

#endif  // SRC_IACT_WORKSPACE_INTERACTIVECONTEXT_H_
