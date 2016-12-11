#include "physicssystem.h"

#include <algorithm>
#include <memory>

#include "components/rigidbody.h"
#include "components/transform.h"
#include "assets/entity.h"

PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

glm::vec2 PhysicsSystem::gravity() const
{
    return _gravity;
}

void PhysicsSystem::setGravity(glm::vec2 gravity)
{
    _gravity = gravity;
}

void PhysicsSystem::update(Time time, const std::vector<EntityHandle>& entities)
{
    for(EntityHandle entity : entities)
    {
        _update(time, entity);
    }
}

void PhysicsSystem::_update(Time time, EntityHandle entity)
{
    std::shared_ptr<Transform> transform = entity->getComponent<Transform>();
    std::shared_ptr<RigidBody> body = entity->getComponent<RigidBody>();

    if(transform == nullptr) { return; }
    if(body == nullptr) { return; }

    //TODO: Gravity
    static const glm::vec2 GRAVITY(0, 1600);
    static const float MAX_FALLSPEED = 300;

    glm::vec2 velocity = body->velocity();
    velocity.y = std::min(velocity.y, MAX_FALLSPEED);
    body->setVelocity(velocity);
    body->setForces(body->forces() + GRAVITY);

    glm::vec2 newPosition = transform->position() +
                            (body->velocity() * time.seconds()) +
                            (body->forces() * (0.5f * time.seconds() * time.seconds()));

    glm::vec2 newVelocity = body->velocity() + (body->forces() * time.seconds());
    newVelocity.y = std::min(newVelocity.y, MAX_FALLSPEED);
    body->setVelocity(newVelocity);

    //TODO: Adjust new position to go to furthest point without collision
    newPosition.y = std::min(newPosition.y, 480.0f); //TODO:
    //

    transform->setPosition(newPosition);

    //TODO: Should this be reset here?
    body->setForces(glm::vec2());
}
