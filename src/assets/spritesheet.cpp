#include "assets/spritesheet.h"

#include "logging.h"

/**
 * @brief SpriteSheet::SpriteSheet
 */
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

bool SpriteSheet::frame(const std::string& name, SpriteSheetFrame& out)
{
    auto it = _frames.find(name);
    if(it != _frames.end())
    {
        out = it->second;
        return true;
    }
    return false;
}

bool SpriteSheet::sequence(const std::string& name, SpriteSheetSequence& out)
{
    auto it = _sequences.find(name);
    if(it != _sequences.end())
    {
        out = it->second;
        return true;
    }
    return false;
}

/**
 * @brief SpriteSheetFrame::SpriteSheetFrame
 * @param pixInfo
 * @param texInfo
 */
SpriteSheetFrame::SpriteSheetFrame()
{
}

SpriteSheetFrame::SpriteSheetFrame(glm::vec4 pixelInfo, glm::vec4 textureCoordInfo)
    : _pixelInfo(pixelInfo),
      _textureCoordInfo(textureCoordInfo)
{
}

SpriteSheetFrame::SpriteSheetFrame(const SpriteSheetFrame& source)
    : _pixelInfo(source._pixelInfo),
      _textureCoordInfo(source._textureCoordInfo)
{
}

glm::vec4 SpriteSheetFrame::pixelInfo() const
{
    return _pixelInfo;
}

glm::vec4 SpriteSheetFrame::textureCoordInfo() const
{
    return _textureCoordInfo;
}

SpriteSheetFrame SpriteSheetFrame::flipped() const
{
    return SpriteSheetFrame(_pixelInfo, glm::vec4(_textureCoordInfo.z,
                                                  _textureCoordInfo.y,
                                                  _textureCoordInfo.x,
                                                  _textureCoordInfo.w));
}

/**
 * @brief SpriteSheetSequence::SpriteSheetSequence
 * @param frames
 * @param millisecondsPerFrame
 * @param flipHorizontal
 */
SpriteSheetSequence::SpriteSheetSequence()
    : _millisecondsPerFrame(0),
      _flipHorizontal(false)
{

}

SpriteSheetSequence::SpriteSheetSequence(std::vector<SpriteSheetFrame> frames, U32 millisecondsPerFrame, bool flipHorizontal)
    : _millisecondsPerFrame(millisecondsPerFrame),
      _flipHorizontal(flipHorizontal)
{
    if(flipHorizontal)
    {
        _frames.reserve(frames.size());

        for(const auto& frame : frames)
        {
            _frames.push_back(frame.flipped());
        }
    }
    else
    {
        _frames = frames;
    }


}

SpriteSheetSequence::SpriteSheetSequence(const SpriteSheetSequence& source)
    : _frames(source._frames),
      _millisecondsPerFrame(source._millisecondsPerFrame),
      _flipHorizontal(source._flipHorizontal)
{
}

bool SpriteSheetSequence::isValid() const
{
    return millisecondsTotal() != 0;
}

const std::vector<SpriteSheetFrame>& SpriteSheetSequence::frames() const
{
    return _frames;
}

U32 SpriteSheetSequence::millisecondsPerFrame() const
{
    return _millisecondsPerFrame;
}

U32 SpriteSheetSequence::millisecondsTotal() const
{
    return (U32)(_millisecondsPerFrame * _frames.size());
}

bool SpriteSheetSequence::flipHorizontal() const
{
    return _flipHorizontal;
}
