#ifndef ANIMATION_H
#define ANIMATION_H

#include "component.h"
#include "assets/spritesheet.h"
#include "utilities/time/time.h"
#include "types.h"

class Animation : public Component
{
public:
    Animation(EntityHandle entity = nullptr);
    ~Animation();

    Component::Type type() const override;

    void update(Time delta);

    const SpriteSheetSequence& sequence() const;
    void setSequence(const SpriteSheetSequence& sequence);

    SpriteSheetFrame currentFrame() const;

private:
    SpriteSheetSequence _sequence;
    Time _time;
};

#endif // ANIMATION_H
