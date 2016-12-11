#ifndef ANIMATION_H
#define ANIMATION_H

#include "assets/component.h"
#include "assets/spritesheet.h"
#include "utilities/time/time.h"
#include "types.h"

class Animation : public Component
{
public:
    Animation(EntityHandle entity = nullptr);
    ~Animation();

    std::type_index type() const override;

    void update(Time delta);

    const SpriteSheetSequence& sequence() const;
    void setSequence(const SpriteSheetSequence& sequence);

    SpriteSheetFrame currentFrame() const;

private:
    SpriteSheetSequence _sequence;
    Time _time;
};

#endif // ANIMATION_H
