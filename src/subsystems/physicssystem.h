#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <vector>

#include <glm/vec2.hpp>

#include "gametime.h"
#include "types.h"

class PhysicsSystem
{
public:
    PhysicsSystem();
    ~PhysicsSystem();

    glm::vec2 gravity() const;
    void setGravity(glm::vec2 gravity);

    void update(GameTime time, const std::vector<EntityHandle>& entities);

private:
    void _update(GameTime time, EntityHandle entity);

private:
    glm::vec2 _gravity;
};

#endif // PHYSICSSYSTEM_H
