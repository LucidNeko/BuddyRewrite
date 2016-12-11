#ifndef ANIMATION_H
#define ANIMATION_H

#include "assets/component.h"
#include "assets/spritesheet.h"
#include "gametime.h"
#include "types.h"

class Animation : public Component
{
public:
    Animation(EntityHandle entity = nullptr);
    ~Animation();

    std::type_index type() const override;

    void update(GameTime delta);

    const SpriteSheetSequence& sequence() const;
    void setSequence(const SpriteSheetSequence& sequence);

    SpriteSheetFrame currentFrame() const;

private:
    SpriteSheetSequence _sequence;
    GameTime _time;
};

#endif // ANIMATION_H
