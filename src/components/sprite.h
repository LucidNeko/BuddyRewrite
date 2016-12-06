#ifndef SPRITE_H
#define SPRITE_H

#include <memory>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "component.h"
#include "types.h"

class Texture;

class Sprite : public Component
{
public:
    Sprite(EntityHandle entity = nullptr);
    ~Sprite();

    Component::Type type() const override;

    SpriteSheetHandle spriteSheet() const;
    void setSpriteSheet(SpriteSheetHandle spriteSheet);

    glm::vec4 textureCoords() const;

    glm::vec3 color() const; //TODO: vec4 to allow transparent modifications?
    void setColor(glm::vec3 color);

    glm::vec2 size() const;
    void setSize(glm::vec2 size);

    U32 currentFrame() const;
    void setCurrentFrame(U32 frame);

    //TODO: Alignment alignment() const;

private:
    SpriteSheetHandle _spriteSheet;
    glm::vec4 _textureCoords;
    glm::vec3 _color;
    glm::vec2 _size;

    U32 _currentFrame;
};

#endif // SPRITE_H
