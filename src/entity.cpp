#include "entity.h"

#include "logging.h"

Entity::Entity(U64 id)
    : _id(id)
{
    LOG_INFO("Entity created: %d", _id);
}

Entity::~Entity()
{
    LOG_INFO("Entity %d destroyed", _id);
}

U64 Entity::id() const
{
    return _id;
}
