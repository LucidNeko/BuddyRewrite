#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include <vector>

#include "types.h"
#include "gametime.h"

class AnimationSystem
{
public:
    AnimationSystem();
    ~AnimationSystem();

    void update(GameTime time, const std::vector<EntityHandle>& entities);

private:
    void _update(GameTime time, EntityHandle entity);
};

#endif // ANIMATIONSYSTEM_H
