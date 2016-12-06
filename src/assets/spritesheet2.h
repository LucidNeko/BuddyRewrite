#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <string>
#include <vector>
#include <unordered_map>

#include "glm/vec4.hpp"

#include "assets/asset.h"
#include "types.h"

class SpriteSheet : public Asset
{
public:
    class Frame
    {
    public:
        glm::vec4 pixInfo;
        glm::vec4 texInfo;
    };

    class Sequence
    {
    public:
        bool flipHorizontal;
        U32 millisecondsPerFrame;
        std::vector<Frame> frames;
    };

public:
    typedef std::unordered_map<std::string, SpriteSheet::Frame> FrameMap;
    typedef std::unordered_map<std::string, SpriteSheet::Sequence> SequenceMap;

public:
    static SpriteSheetHandle load(const std::string& filepath, class Assets* loader);

public:
    ~SpriteSheet();

    TextureHandle texture() const;

    bool frame(const std::string& name, Frame& out);
    bool sequence(const std::string& name, SpriteSheet::Sequence& out);

private:
    SpriteSheet();
    SpriteSheet(TextureHandle texture);

    TextureHandle _texture;

    FrameMap _frames;
    SequenceMap _sequences;

};

#endif // SPRITESHEET_H
