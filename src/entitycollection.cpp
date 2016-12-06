#include "entitycollection.h"

#include <algorithm>

#include "entity.h"

EntityCollection::EntityCollection()
{

}

EntityCollection::~EntityCollection()
{

}

bool EntityCollection::add(EntityHandle entity)
{
    //TODO: Make this efficient
    for(EntityHandle e : _entities)
    {
        if(e == entity)
        {
            return false;
        }
    }

    _entities.push_back(entity);
    return true;
}

EntityHandle EntityCollection::remove(U64 id)
{
    //TODO: Make this efficient
    auto result = std::find_if(std::begin(_entities), std::end(_entities), [id](EntityHandle entity){ return entity->id() == id; });
    if(result != std::end(_entities))
    {
        EntityHandle entity = *result;
        _entities.erase(result);
        return entity;
    }
    else
    {
        return EntityHandle();
    }
}

EntityHandle EntityCollection::get(U64 id) const
{
    //TODO: Make this efficient
    auto result = std::find_if(std::begin(_entities), std::end(_entities), [id](EntityHandle entity){ return entity->id() == id; });
    if(result != std::end(_entities))
    {
        return *result;
    }
    else
    {
        return EntityHandle();
    }
}

std::vector<EntityHandle>& EntityCollection::entities()
{
    return _entities;
}
