#include "rigidbody.h"

RigidBody::RigidBody(EntityHandle entity)
    : Component(entity)
{
}

RigidBody::~RigidBody()
{
}

std::type_index RigidBody::type() const
{
    return std::type_index(typeid(RigidBody));
}

glm::vec2 RigidBody::velocity()
{
    return _velocity;
}

void RigidBody::setVelocity(glm::vec2 velocity)
{
    _velocity = velocity;
}

glm::vec2 RigidBody::forces()
{
    return _forces;
}

void RigidBody::setForces(glm::vec2 forces)
{
    _forces = forces;
}
