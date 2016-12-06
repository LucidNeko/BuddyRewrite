#include "sprite.h"

#include "logging.h"
#include "resources/spritesheet.h"
#include "resources/texture.h"

Sprite::Sprite(EntityHandle entity)
    : Component(entity),
      _spriteSheet(),
      _textureCoords(),
      _color(1, 1, 1),
      _size(),
      _currentFrame(0)
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
    if(!_spriteSheet) { return glm::vec4(); }

    SpriteSheet::Info info = _spriteSheet->info();

    U32 columns = info.columns;
    U32 rows = info.rows;

    U32 row = _currentFrame / columns;
    U32 col = _currentFrame - row * columns;

    F32 dx = F32(col) / F32(columns);
    F32 dy = F32(row) / F32(rows);

    F32 w = 1.0f / F32(columns);
    F32 h = 1.0f / F32(rows);

    F32 x = dx + w*col;
    F32 y = dy + h*row;

    return glm::vec4(x, y, x + w, y + h);
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

U32 Sprite::currentFrame() const
{
    return _currentFrame;
}

void Sprite::setCurrentFrame(U32 frame)
{
    _currentFrame = frame;
}
