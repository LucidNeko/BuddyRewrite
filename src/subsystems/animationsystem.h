#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include <vector>

#include "types.h"
#include "utilities/time/time.h"

class AnimationSystem
{
public:
    AnimationSystem();
    ~AnimationSystem();

    void update(Time time, const std::vector<EntityHandle>& entities);

private:
    void _update(Time time, EntityHandle entity);
};

#endif // ANIMATIONSYSTEM_H
