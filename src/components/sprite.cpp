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

std::type_index Sprite::type() const
{
    return std::type_index(typeid(Sprite));
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
    return _current.textureCoordInfo();
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

SpriteSheetFrame Sprite::currentFrame() const
{
    return _current;
}

void Sprite::setCurrentFrame(const SpriteSheetFrame& frame)
{
    _current = frame;
}
