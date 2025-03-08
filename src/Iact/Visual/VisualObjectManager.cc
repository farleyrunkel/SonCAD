// Copyright [2024] SunCAD

// Own include
#include "Iact/Visual/VisualObjectManager.h"

// Standard includes
#include <algorithm>
#include <iostream>

// boost includes
#include <boost/uuid/uuid.hpp>

// Occt includes
#include <AIS_InteractiveObject.hxx>
#include <Standard_Handle.hxx>

// Project includes
#include "Core/Topology/Body.h"
#include "Core/Topology/Entity.h"
#include "Core/Topology/Layer.h"
#include "Iact/Visual/VisualObject.h"
#include "Iact/Workspace/InteractiveContext.h"
#include "Iact/Workspace/WorkspaceController.h"

std::unordered_map<std::string, VisualObjectManager::CreateVisualObjectDelegate> VisualObjectManager::s_registeredVisualTypes;

VisualObjectManager::VisualObjectManager(std::shared_ptr<WorkspaceController> workspaceController)
    : m_workspaceController(std::move(workspaceController))
{
    // 假设外部信号中心已转换为 Boost.Signals2，需手动连接
    // Entity_SignalHub::instance()->entityRemoved.connect([this](auto* e) { entity_EntityRemoved(std::shared_ptr<Entity>(e)); });
    // InteractiveEntity_SignalHub::instance()->visualChanged.connect([this](auto* e) { interactiveEntity_VisualChanged(std::shared_ptr<InteractiveEntity>(e)); });
    // Layer_SignalHub::instance()->interactivityChanged.connect([this](auto* l) { layer_InteractivityChanged(std::shared_ptr<Layer>(l)); });
}

std::shared_ptr<VisualObject> VisualObjectManager::createVisualObject(std::shared_ptr<WorkspaceController> workspaceController,
                                                                      std::shared_ptr<InteractiveEntity> entity)
{
    if(!entity)
    {
        std::cerr << "Entity is null, cannot create visual object." << std::endl;
        return nullptr;
    }

    std::string typeName = typeid(*entity).name();
    auto it = s_registeredVisualTypes.find(typeName);
    if(it == s_registeredVisualTypes.end())
    {
        std::cerr << "No registered visual object for entity type " << typeName << std::endl;
        return nullptr;
    }

    try
    {
        return it->second(workspaceController, entity);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error creating visual object for entity type " << typeName << ": " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "Unknown error occurred while creating visual object for entity type " << typeName << std::endl;
    }
    return nullptr;
}

std::shared_ptr<VisualObject> VisualObjectManager::get(std::shared_ptr<InteractiveEntity> body, bool forceCreation)
{
    if(!body) return nullptr;

    auto it = m_interactiveToVisualDictionary.find(body);
    if(it != m_interactiveToVisualDictionary.end())
    {
        return it->second;
    }

    if(forceCreation)
    {
        return add(body);
    }
    return nullptr;
}

std::shared_ptr<VisualObject> VisualObjectManager::add(std::shared_ptr<InteractiveEntity> entity)
{
    auto visualObject = get(entity);
    if(visualObject)
    {
        visualObject->update();
    }
    else
    {
        visualObject = createVisualObject(m_workspaceController, entity);
        if(visualObject)
        {
            m_interactiveToVisualDictionary[entity] = visualObject;
            m_uuidToInteractiveDictionary[entity->uuid()] = entity; // 假设 guid() 返回 boost::uuids::uuid
        }
    }
    return visualObject;
}

void VisualObjectManager::remove(std::shared_ptr<InteractiveEntity> entity)
{
    auto it = m_interactiveToVisualDictionary.find(entity);
    if(it != m_interactiveToVisualDictionary.end())
    {
        it->second->remove();
        m_interactiveToVisualDictionary.erase(it);
        m_uuidToInteractiveDictionary.erase(entity->uuid());
        m_invalidatedInteractiveEntities.erase(
            std::remove(m_invalidatedInteractiveEntities.begin(), m_invalidatedInteractiveEntities.end(), entity),
            m_invalidatedInteractiveEntities.end()
        );
    }
}

void VisualObjectManager::update(std::shared_ptr<InteractiveEntity> body)
{
    if(!body) return;

    //if(!body->isVisible() || (body->layer() && !body->layer()->isVisible()))
    //{
    //    remove(body);
    //    return;
    //}

    auto visualObject = get(body);
    if(!visualObject)
    {
        add(body);
        return;
    }
    visualObject->update();
}

std::shared_ptr<InteractiveEntity> VisualObjectManager::getEntity(const Handle(AIS_InteractiveObject)& aisInteractiveObject)
{
    if(aisInteractiveObject.IsNull()) return nullptr;

    auto owner = aisInteractiveObject->GetOwner();
    boost::uuids::uuid uuid;
    //if(!AISX_Guid::tryGetGuid(owner, uuid))
    //{ // 假设 tryGetGuid 已适配 Boost UUID
    //    return nullptr;
    //}

    auto it = m_uuidToInteractiveDictionary.find(uuid);
    return (it != m_uuidToInteractiveDictionary.end()) ? it->second : nullptr;
}

void VisualObjectManager::updateInvalidatedEntities()
{
    for(auto& entity : m_invalidatedInteractiveEntities)
    {
        update(entity);
    }
    m_invalidatedInteractiveEntities.clear();
}

std::vector<std::shared_ptr<VisualObject>> VisualObjectManager::getAll() const
{
    std::vector<std::shared_ptr<VisualObject>> result;
    result.reserve(m_interactiveToVisualDictionary.size());
    for(const auto& pair : m_interactiveToVisualDictionary)
    {
        result.push_back(pair.second);
    }
    return result;
}

std::vector<std::shared_ptr<VisualObject>> VisualObjectManager::select(std::function<bool(std::shared_ptr<InteractiveEntity>)> selector) const
{
    std::vector<std::shared_ptr<VisualObject>> result;
    for(const auto& pair : m_interactiveToVisualDictionary)
    {
        if(selector(pair.first))
        {
            result.push_back(pair.second);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Body>> VisualObjectManager::getIsolatedEntities() const
{
    return m_isolatedEntities;
}

void VisualObjectManager::setIsolatedEntities(const std::vector<std::shared_ptr<Body>>& entities)
{
    m_isolatedEntities = entities;
    entityIsolationChanged(!m_isolatedEntities.empty());
    isolatedEntitiesChanged(this);
}

void VisualObjectManager::entity_EntityRemoved(std::shared_ptr<Entity> entity)
{
    auto interactiveEntity = std::dynamic_pointer_cast<InteractiveEntity>(entity);
    if(!interactiveEntity) return;

    m_invalidatedInteractiveEntities.erase(
        std::remove(m_invalidatedInteractiveEntities.begin(), m_invalidatedInteractiveEntities.end(), interactiveEntity),
        m_invalidatedInteractiveEntities.end()
    );
    remove(interactiveEntity);
}

void VisualObjectManager::interactiveEntity_VisualChanged(std::shared_ptr<InteractiveEntity> entity)
{
    if(std::find(m_invalidatedInteractiveEntities.begin(), m_invalidatedInteractiveEntities.end(), entity) == m_invalidatedInteractiveEntities.end())
    {
        m_invalidatedInteractiveEntities.push_back(entity);
    }
    m_workspaceController->invalidate();
}

void VisualObjectManager::layer_InteractivityChanged(std::shared_ptr<Layer> /*layer*/)
{
    m_workspaceController->invalidate();
}