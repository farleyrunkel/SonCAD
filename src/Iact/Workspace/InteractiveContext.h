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

#include "Iact/Workspace/WorkspaceController.h"
#include "Iact/Workspace/ModelController.h"

class ViewportController : public QObject {
    Q_OBJECT

 public:
    explicit ViewportController(QObject* parent = nullptr) : QObject(parent) {}

    Viewport* viewport() { return nullptr; }
};

class InteractiveContext : public CoreContext {
    Q_OBJECT
        Q_PROPERTY(ModelController* documentController READ documentController WRITE setDocumentController NOTIFY documentControllerChanged)
        Q_PROPERTY(WorkspaceController* workspaceController READ workspaceController NOTIFY workspaceControllerChanged)
        Q_PROPERTY(ViewportController* viewportController READ viewportController NOTIFY viewportControllerChanged)
        Q_PROPERTY(QList<QColor> recentUsedColors READ recentUsedColors NOTIFY recentUsedColorsChanged)
        Q_PROPERTY(QList<QString> recentUsedScripts READ recentUsedScripts NOTIFY recentUsedScriptsChanged)

 public:
    InteractiveContext()
        : CoreContext(),
        _documentController(new ModelController(this)),
        _workspaceController(nullptr),
        _viewportController(nullptr) {
        initialize();
    }

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

    // RecentUsedColors getter
    QList<QColor> recentUsedColors() const;

    // RecentUsedScripts getter
    QList<QString> recentUsedScripts() const;

    void addToScriptMruList(const QString& filePath);

 signals:
    void documentControllerChanged();
    void workspaceControllerChanged();
    void viewportControllerChanged();
    void recentUsedColorsChanged();
    void recentUsedScriptsChanged();

 private:
    ModelController* _documentController;
    WorkspaceController* _workspaceController;
    ViewportController* _viewportController;

    QList<QColor> _recentUsedColors;
    QList<QString> _recentUsedScripts;
    const int _maxScriptMruCount = 10;

    void initialize() {}
};

#endif  // SRC_IACT_WORKSPACE_INTERACTIVECONTEXT_H_
