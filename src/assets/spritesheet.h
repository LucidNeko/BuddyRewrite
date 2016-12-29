#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <string>
#include <vector>
#include <unordered_map>

#include "glm/vec4.hpp"

#include "assets/asset.h"
#include "types.h"

class SpriteSheetFrame
{
public:
    SpriteSheetFrame();
    SpriteSheetFrame(glm::vec4 pixelInfo, glm::vec4 textureCoordInfo);
    SpriteSheetFrame(const SpriteSheetFrame& source);

    glm::vec4 pixelInfo() const;
    glm::vec4 textureCoordInfo() const;

    SpriteSheetFrame flipped() const;

private:
    glm::vec4 _pixelInfo;
    glm::vec4 _textureCoordInfo;
};

class SpriteSheetSequence
{
public:
    SpriteSheetSequence();
    SpriteSheetSequence(std::vector<SpriteSheetFrame> frames, U32 millisecondsPerFrame, bool flipHorizontal);
    SpriteSheetSequence(const SpriteSheetSequence& source);

    bool isValid() const;

    const std::vector<SpriteSheetFrame>& frames() const;
    U32 millisecondsPerFrame() const;
    U32 millisecondsTotal() const;
    bool flipHorizontal() const;

private:
    std::vector<SpriteSheetFrame> _frames;
    U32 _millisecondsPerFrame;
    bool _flipHorizontal;
};

struct SpriteSheetDefinition
{
public:
    // TODO: Not duplicate these typedefs?
    typedef std::unordered_map<std::string, SpriteSheetFrame> FrameMap;
    typedef std::unordered_map<std::string, SpriteSheetSequence> SequenceMap;

public:
    TextureHandle texture;
    FrameMap frames;
    SequenceMap sequences;
};

class SpriteSheet : public Asset
{
public:
    typedef std::unordered_map<std::string, SpriteSheetFrame> FrameMap;
    typedef std::unordered_map<std::string, SpriteSheetSequence> SequenceMap;

public:
    static SpriteSheetHandle load(const std::string& filepath, AssetsHandle loader);

public:
    SpriteSheet(const SpriteSheetDefinition& definition);
    ~SpriteSheet();

    TextureHandle texture() const;

    bool frame(const std::string& name, SpriteSheetFrame& out);
    bool sequence(const std::string& name, SpriteSheetSequence& out);

private:
    TextureHandle _texture;

    FrameMap _frames;
    SequenceMap _sequences;

};

#endif // SPRITESHEET_H
