#include "components/component.h"

#include "logging.h"

Component::Component(EntityHandle entity)
    : _entity(entity)
{
}

Component::~Component()
{
}

// TODO: Can't use typeName in the destructor because it calls type() on extended class.
const char* Component::typeName() const
{
    switch (type()) {
    case Collider:
        return "Collider";
    case RigidBody:
        return "RigidBody";
    case Sprite:
        return "Sprite";
    case SpriteRenderer:
        return "SpriteRenderer";
    case Transform:
        return "Transform";
    case Script:
        return "Script";
    default:
        return "Unknown";
    }
}

EntityHandle Component::entity() const
{
    return _entity.lock();
}
