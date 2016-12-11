#include "components/animation.h"


Animation::Animation(EntityHandle entity)
    : Component(entity)
{

}

Animation::~Animation()
{
}

std::type_index Animation::type() const
{
    return std::type_index(typeid(Animation));
}

void Animation::update(Time delta)
{
    _time += delta;

    U64 sequenceTime = _sequence.millisecondsTotal();
    if(sequenceTime != 0)
    {
        _time = Time::fromMilliseconds(_time.milliseconds() % sequenceTime);
    }
}

const SpriteSheetSequence& Animation::sequence() const
{
    return _sequence;
}

void Animation::setSequence(const SpriteSheetSequence& sequence)
{
    _time = Time();
    _sequence = sequence;
}

SpriteSheetFrame Animation::currentFrame() const
{
    if(!_sequence.isValid()) { return SpriteSheetFrame(); }

    U32 milliseconds = U32(_time.milliseconds());
    U32 frameNumber = milliseconds / _sequence.millisecondsPerFrame();

    const std::vector<SpriteSheetFrame>& frames = _sequence.frames();

    assert(frameNumber < frames.size());

    return frames.at(frameNumber);
}
