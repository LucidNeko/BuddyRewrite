#include "componentfactory.h"

#include "collider.h"
#include "rigidbody.h"
#include "transform.h"

ComponentFactory::ComponentFactory()
{
}

ComponentFactory::~ComponentFactory()
{
}

ComponentHandle ComponentFactory::create(Component::Type type, EntityHandle entity) const
{
    switch(type)
    {
    case Component::Transform :
        return ComponentHandle(new Transform(entity));
    case Component::Collider :
        return ComponentHandle(new Collider(entity));
    case Component::RigidBody :
        return ComponentHandle(new RigidBody(entity));
    default:
        return ComponentHandle();
    }
}
