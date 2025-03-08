// Copyright [2024] SunCAD

#ifndef IACT_VISUAL_VISUALOBJECTMANAGER_H_
#define IACT_VISUAL_VISUALOBJECTMANAGER_H_

// Standard includes
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

// Boost includes
#include <boost/signals2.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/functional/hash.hpp>

// OCCT includes
#include <AIS_InteractiveContext.hxx>
#include <gp_Trsf.hxx>
#include <Standard_Handle.hxx>

// Project includes
#include "Core/Topology/InteractiveEntity.h"
#include "Occt/AisExtensions/AISX_Guid.h"

// Forward declarations
class WorkspaceController;
class Body;
class VisualObject;
class Entity;
class Layer;

class VisualObjectManager
{
public:
    using Ptr = std::shared_ptr<VisualObjectManager>;
    using CreateVisualObjectDelegate = std::function<std::shared_ptr<VisualObject>(std::shared_ptr<WorkspaceController>, std::shared_ptr<InteractiveEntity>)>;

    explicit VisualObjectManager(std::shared_ptr<WorkspaceController> workspaceController);
    ~VisualObjectManager() = default;

    template<typename TEntity>
    static void registerEntity(CreateVisualObjectDelegate createDelegate)
    {
        std::string typeName = typeid(TEntity).name();
        if(s_registeredVisualTypes.find(typeName) != s_registeredVisualTypes.end())
        {
            std::cerr << "Body type " << typeName << " has already been registered." << std::endl;
            return;
        }
        s_registeredVisualTypes[typeName] = std::move(createDelegate);
    }

    std::shared_ptr<VisualObject> createVisualObject(std::shared_ptr<WorkspaceController> workspaceController,
                                                     std::shared_ptr<InteractiveEntity> entity);
    std::shared_ptr<VisualObject> get(std::shared_ptr<InteractiveEntity> body, bool forceCreation = false);
    std::shared_ptr<VisualObject> add(std::shared_ptr<InteractiveEntity> body);

    void update(std::shared_ptr<InteractiveEntity> body);

    std::shared_ptr<InteractiveEntity> getEntity(const Handle(AIS_InteractiveObject)& aisInteractiveObject);

    void remove(std::shared_ptr<InteractiveEntity> body);

    void updateInvalidatedEntities();

    std::vector<std::shared_ptr<VisualObject>> getAll() const;
    std::vector<std::shared_ptr<VisualObject>> select(std::function<bool(std::shared_ptr<InteractiveEntity>)> selector) const;

    std::vector<std::shared_ptr<Body>> getIsolatedEntities() const;
    void setIsolatedEntities(const std::vector<std::shared_ptr<Body>>& entities);

public: // Signals
    boost::signals2::signal<void(bool)> entityIsolationChanged;
    boost::signals2::signal<void(VisualObjectManager*)> isolatedEntitiesChanged;

private:
    void entity_EntityRemoved(std::shared_ptr<Entity> entity);
    void layer_InteractivityChanged(std::shared_ptr<Layer> layer);
    void interactiveEntity_VisualChanged(std::shared_ptr<InteractiveEntity> entity);

private:
    std::shared_ptr<WorkspaceController> m_workspaceController;
    std::vector<std::shared_ptr<InteractiveEntity>> m_invalidatedInteractiveEntities;
    std::vector<std::shared_ptr<Body>> m_isolatedEntities;

    std::unordered_map<std::shared_ptr<InteractiveEntity>, std::shared_ptr<VisualObject>> m_interactiveToVisualDictionary;
    std::unordered_map<boost::uuids::uuid, std::shared_ptr<InteractiveEntity>, boost::hash<boost::uuids::uuid>> m_uuidToInteractiveDictionary;

    static std::unordered_map<std::string, CreateVisualObjectDelegate> s_registeredVisualTypes;
};

#endif // IACT_VISUAL_VISUALOBJECTMANAGER_H_