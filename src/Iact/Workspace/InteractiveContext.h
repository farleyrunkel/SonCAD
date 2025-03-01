// Copyright [2024] SunCAD

#ifndef APP_INTERACTIVECONTEXT_H
#define APP_INTERACTIVECONTEXT_H

#include <QColor>
#include <QList>
#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QString>

#include "Comm/BaseObject.h"
#include "Core/CoreContext.h"
#include "Iact/Workspace/ModelController.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Workspace/WorkspaceController.h"

DEFINE_STANDARD_HANDLE(InteractiveContext, CoreContext)

class InteractiveContext : public CoreContext
{
public:
    InteractiveContext();

    ~InteractiveContext() override;

    // ModelController getter/setter
    Handle(ModelController) GetDocumentController() const;
    void SetDocumentController(const Handle(ModelController)& controller);

    // WorkspaceController getter/setter
    Handle(WorkspaceController) GetWorkspaceController() const;
    void SetWorkspaceController(const Handle(WorkspaceController)& controller);

    // ViewportController getter/setter
    Handle(ViewportController) GetViewportController() const;
    void SetViewportController(const Handle(ViewportController)& controller);

    // RecentUsedColors getter
    QList<QColor> RecentUsedColors() const;

    // RecentUsedScripts getter
    QList<QString> RecentUsedScripts() const;

    // 添加脚本到最近使用列表
    void AddToScriptMruList(const QString& filePath);

private:
    Handle(ModelController) _DocumentController;
    Handle(WorkspaceController) _WorkspaceController;
    Handle(ViewportController) _ViewportController;

    QList<QColor> _RecentUsedColors;
    QList<QString> _RecentUsedScripts;
    const int _MaxScriptMruCount = 10;

    void Initialize()
    {}
};

#endif  // APP_INTERACTIVECONTEXT_H
