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
