#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <string>
#include <vector>
#include <unordered_map>

#include "glm/vec4.hpp"

#include "assets/asset.h"
#include "types.h"

class SpriteSheet2 : public Asset
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
    typedef std::unordered_map<std::string, SpriteSheet2::Frame> FrameMap;
    typedef std::unordered_map<std::string, SpriteSheet2::Sequence> SequenceMap;

public:
    static SpriteSheet2Handle load(const std::string& filepath, class Assets* loader);

public:
    ~SpriteSheet2();

    Texture2Handle texture() const;

    bool frame(const std::string& name, Frame& out);
    bool sequence(const std::string& name, SpriteSheet2::Sequence& out);

private:
    SpriteSheet2();
    SpriteSheet2(Texture2Handle texture);

    Texture2Handle _texture;

    FrameMap _frames;
    SequenceMap _sequences;

};

#endif // SPRITESHEET_H
