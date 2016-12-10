#include "subsystems/animationsystem.h"

#include "components/animation.h"
#include "components/sprite.h"
#include "entity.h"

AnimationSystem::AnimationSystem()
{
}

AnimationSystem::~AnimationSystem()
{
}

void AnimationSystem::update(Time time, const std::vector<EntityHandle>& entities)
{
    for(EntityHandle entity : entities)
    {
        _update(time, entity);
    }
}

void AnimationSystem::_update(Time time, EntityHandle entity)
{
    if(auto animation = entity->getComponent<Animation>())
    {
        animation->update(time);

        if(auto sprite = entity->getComponent<Sprite>())
        {
            sprite->setCurrentFrame(animation->currentFrame());
        }
    }
}
