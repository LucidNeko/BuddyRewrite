#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/vec2.hpp>

#include "component.h"

class RigidBody : public Component
{
public:
    RigidBody(EntityHandle entity = nullptr);
    ~RigidBody();

    std::type_index type() const override;

    glm::vec2 velocity();
    void setVelocity(glm::vec2 velocity);

    glm::vec2 forces();
    void setForces(glm::vec2 forces);

private:
    glm::vec2 _velocity;
    glm::vec2 _forces;
};

#endif // RIGIDBODY_H
