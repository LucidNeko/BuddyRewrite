#include "assets/spritesheet2.h"

#include "logging.h"

SpriteSheet2::SpriteSheet2()
{
}

SpriteSheet2::SpriteSheet2(Texture2Handle texture)
    : _texture(texture)
{
}

SpriteSheet2::~SpriteSheet2()
{
    LOG_INFO("SS2 Destroyed");
}

Texture2Handle SpriteSheet2::texture() const
{
    return _texture;
}

bool SpriteSheet2::frame(const std::string& name, SpriteSheet2::Frame& out)
{
    auto it = _frames.find(name);
    if(it != _frames.end())
    {
        out = it->second;
        return true;
    }
    return false;
}

bool SpriteSheet2::sequence(const std::string& name, Sequence& out)
{
    auto it = _sequences.find(name);
    if(it != _sequences.end())
    {
        out = it->second;
        return true;
    }
    return false;
}
