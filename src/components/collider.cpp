#include "collider.h"

Collider::Collider(EntityHandle entity)
    : Component(entity)
{
}

Collider::~Collider()
{
}

std::type_index Collider::type() const
{
    return std::type_index(typeid(Collider));
}
