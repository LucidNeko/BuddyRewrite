#include "scene.h"

#include <algorithm>
#include <iterator>
#include <vector>

#include "assets/assets.h"
#include "entity.h"
#include "logging.h"

Scene::Scene(AssetsHandle assets)
    : _assets(assets)
{
}

Scene::~Scene()
{
}

void Scene::add(EntityHandle entity)
{
    if(!entity)
    {
        LOG_ERROR("Failed to add entity, because it is null");
        return;
    }

    U64 key = entity->id();
    if(_entities.find(key) == _entities.end())
    {
        _entities[key] = entity;
    }
    else
    {
        LOG_ERROR("Failed to add entity, because an entity with id=%llu already exists in the scene.", key);
    }
}

bool Scene::remove(EntityHandle entity)
{
    return remove(entity->id());
}

bool Scene::remove(U64 entityId)
{
    return _entities.erase(entityId) != 0;
}

void Scene::removeAll()
{
    _entities.clear();
}

EntityHandle Scene::get(U64 entityId)
{
    if(_entities.find(entityId) != _entities.end())
    {
        return _entities[entityId];
    }
    return EntityHandle();
}

std::vector<EntityHandle> Scene::getAll()
{
    std::vector<EntityHandle> out;
    std::transform(std::begin(_entities), std::end(_entities), std::back_inserter(out), [](auto& pair){ return pair.second; });
    return out;
}
