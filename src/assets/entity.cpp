#include "entity.h"

#include "logging.h"

Entity::Entity(Uuid id)
    : _id(id)
{
    LOG_INFO("Entity created: %s", _id.toString().c_str());
}

Entity::~Entity()
{
    LOG_INFO("Entity %s destroyed", _id.toString().c_str());
}

Uuid Entity::id() const
{
    return _id;
}

void Entity::addComponent(ComponentHandle component)
{
    LOG_INFO("Adding: %s", component->typeName().c_str());

    if(component->entity())
    {
        LOG_ERROR("%s Component already had an owner, probably a bug", component->typeName());
    }

    //TODO: detatch from previous entity?
    component->setEntity(shared_from_this());

    std::type_index type = component->type();
    _components[type].push_back(component);
}

ComponentHandle Entity::getComponent(std::type_index type)
{
    auto it = _components.find(type);
    if(it != _components.end() && !it->second.empty())
    {
        return it->second.front();
    }
    return ComponentHandle();
}

const std::vector<ComponentHandle>& Entity::getComponents(std::type_index type)
{
    auto it = _components.find(type);
    if(it != _components.end())
    {
        return it->second;
    }

    static std::vector<ComponentHandle> empty;
    return empty;
}
