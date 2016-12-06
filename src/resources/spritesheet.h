#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "resources/texture.h"
#include "types.h"

class SpriteSheet : public Texture
{
public:
    struct Info
    {
        U32 frameWidth;
        U32 frameHeight;

        U32 rows;
        U32 columns;

        I32 fps;
    };

public:
    SpriteSheet(std::string name);
    ~SpriteSheet();

    bool load() override;
    void destroy() override;

    SpriteSheet::Info info() const;

public:
    static Resource::Type type() { return TYPE_SPRITE_SHEET; }

private:
    Info _info;
};

#endif // SPRITESHEET_H
