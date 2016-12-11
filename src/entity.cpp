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
    _components.add(component);
}
