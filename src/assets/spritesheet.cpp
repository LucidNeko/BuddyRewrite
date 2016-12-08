#include "assets/spritesheet.h"

#include "logging.h"

SpriteSheet::SpriteSheet()
{
    LOG_INFO("SpriteSheet Created");
}

SpriteSheet::SpriteSheet(TextureHandle texture)
    : _texture(texture)
{
}

SpriteSheet::~SpriteSheet()
{
    LOG_INFO("SpriteSheet Destroyed");
}

TextureHandle SpriteSheet::texture() const
{
    return _texture;
}

bool SpriteSheet::frame(const std::string& name, SpriteSheet::Frame& out)
{
    auto it = _frames.find(name);
    if(it != _frames.end())
    {
        out = it->second;
        return true;
    }
    return false;
}

bool SpriteSheet::sequence(const std::string& name, Sequence& out)
{
    auto it = _sequences.find(name);
    if(it != _sequences.end())
    {
        out = it->second;
        return true;
    }
    return false;
}
