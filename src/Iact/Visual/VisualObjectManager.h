#ifndef SRC_IACT_VISUAL_VISUALOBJECTMANAGER_H_
#define SRC_IACT_VISUAL_VISUALOBJECTMANAGER_H_

#include <QObject>
#include <QMap>
#include <QList>
#include <functional>

#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>
#include <AIS_InteractiveObject.hxx>
#include <TCollection_ExtendedString.hxx>

#include "Comm/BaseObject.h"
#include "Core/Topology/InteractiveEntity.h"
#include "Core/Topology/Layer.h"
#include "Iact/Visual/VisualObject.h"

class Sun_WorkspaceController;

DEFINE_STANDARD_HANDLE(Sun_VisualObjectManager, Standard_Transient);

class Sun_VisualObjectManager : public Sun_BaseObject
{
    Q_OBJECT
    Q_PROPERTY(bool entityIsolationEnabled READ EntityIsolationEnabled NOTIFY isolationChanged)

public:
    using CreateVisualObjectDelegate = std::function<Handle(Sun_VisualObject)(Sun_WorkspaceController*, const Handle(Sun_InteractiveEntity)&)>;

    explicit Sun_VisualObjectManager(const Handle(Sun_WorkspaceController) workspaceController)
        : _workspaceController(workspaceController) {}

    ~Sun_VisualObjectManager() override {
        Clear();
    }

    // Registration methods
    template <typename TEntity>
    static void Register(const CreateVisualObjectDelegate& createDelegate) {
        auto typeId = TEntity::GetTypeId();
        Q_ASSERT(!_registeredVisualTypes.contains(typeId) && "Entity type already registered.");
        _registeredVisualTypes[typeId] = createDelegate;
    }

    Handle(Sun_VisualObject) Add(const Handle(Sun_InteractiveEntity)& entity) {
        if (!entity) return nullptr;

        //if (_interactiveToVisual.contains(entity)) {
        //    auto visualObject = _interactiveToVisual[entity];
        //    visualObject->Update();
        //    return visualObject;
        //}

        auto visualObject = CreateVisualObject(_workspaceController, entity);
        //if (visualObject) {
        //    _interactiveToVisual[entity] = visualObject;
        //    _guidToInteractive[entity->GetGUID()] = entity;
        //}
        return visualObject;
    }

    Handle(Sun_VisualObject) Get(const Handle(Sun_InteractiveEntity)& entity, bool) const {
        return _interactiveToVisual.value(entity, nullptr);
    }

    QList<Handle(Sun_VisualObject)> GetAll() const {
        return _interactiveToVisual.values();
    }

    void Remove(const Handle(Sun_InteractiveEntity)& entity) {
        //auto visualObject = _interactiveToVisual.take(entity);
        //if (visualObject) {
        //    visualObject->Remove();
        //}
        //_guidToInteractive.remove(entity->GetGUID());
        //_invalidatedEntities.removeAll(entity);
    }

    void Clear() {
        //for (auto visualObject : _interactiveToVisual) {
        //    visualObject->Remove();
        //}
        //_interactiveToVisual.clear();
        //_guidToInteractive.clear();
        //_invalidatedEntities.clear();
        //_isolatedEntities.clear();
    }

    // Isolation
    bool EntityIsolationEnabled() const {
        return !_isolatedEntities.isEmpty();
    }

    void SetIsolatedEntities(const QList<Handle(Sun_InteractiveEntity)>& entitiesToIsolate) {
        _isolatedEntities = entitiesToIsolate;
        emit isolationChanged();
    }

    QList<Handle(Sun_InteractiveEntity)> GetIsolatedEntities() const {
        return _isolatedEntities;
    }

signals:
    void isolationChanged();

private:
    static Handle(Sun_VisualObject) CreateVisualObject(const Handle(Sun_WorkspaceController)& workspaceController,
                                                       const Handle(Sun_InteractiveEntity)& entity) {
        //auto typeId = entity->DynamicType();
        //if (_registeredVisualTypes.contains(typeId)) {
        //    return _registeredVisualTypes[typeId](workspaceController, entity);
        //}

        //// Fallback logic if no delegate is registered
        //qWarning() << "No visualization registered for entity type" << typeId;
        //return nullptr;
    }

private:
    static QMap<Standard_Type, CreateVisualObjectDelegate> _registeredVisualTypes;

    Handle(Sun_WorkspaceController)  _workspaceController = nullptr;
    QMap<Handle(Sun_InteractiveEntity), Handle(Sun_VisualObject)> _interactiveToVisual;
    QMap<TCollection_ExtendedString, Handle(Sun_InteractiveEntity)> _guidToInteractive;
    QList<Handle(Sun_InteractiveEntity)> _invalidatedEntities;
    QList<Handle(Sun_InteractiveEntity)> _isolatedEntities;
};

#endif  // SRC_IACT_VISUAL_VISUALOBJECTMANAGER_H_
