#include "collider.h"

Collider::Collider(EntityHandle entity)
    : Component(entity)
{
}

Collider::~Collider()
{
}

Component::Type Collider::type() const
{
    return Type::Collider;
}
