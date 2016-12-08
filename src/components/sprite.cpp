#include "sprite.h"

#include "logging.h"
#include "assets/spritesheet.h"
#include "assets/texture.h"

Sprite::Sprite(EntityHandle entity)
    : Component(entity),
      _spriteSheet(),
      _textureCoords(),
      _color(1, 1, 1),
      _size(),
      _currentFrame("")
{
}

Sprite::~Sprite()
{
}

Component::Type Sprite::type() const
{
    return Component::Sprite;
}

SpriteSheetHandle Sprite::spriteSheet() const
{
     return _spriteSheet;
}

void Sprite::setSpriteSheet(SpriteSheetHandle spriteSheet)
{
    _spriteSheet = spriteSheet;
}

glm::vec4 Sprite::textureCoords() const
{
    SpriteSheet::Frame frame;

    if(_spriteSheet && _spriteSheet->frame(_currentFrame, frame))
    {
        return frame.texInfo;
    }
    return glm::vec4();
}

glm::vec3 Sprite::color() const
{
    return _color;
}

void Sprite::setColor(glm::vec3 color)
{
    _color = color;
}

glm::vec2 Sprite::size() const
{
    return _size;
}

void Sprite::setSize(glm::vec2 size)
{
    _size = size;
}

std::string Sprite::currentFrame() const
{
    return _currentFrame;
}

void Sprite::setCurrentFrame(std::string frame)
{
    _currentFrame = frame;
}
