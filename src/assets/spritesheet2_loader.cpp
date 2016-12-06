#include "assets/spritesheet2.h"

#include <fstream>

#include "json.hpp"

#include "assets/assets.h"
#include "assets/texture2.h"

#include "logging.h"

//class Frame
//{
//public:
//    glm::vec4 pixInfo;
//    glm::vec4 texInfo;
//};

//class Sequence
//{
//public:
//    bool flipHorizontal;
//    U32 millisecondsPerFrame;
//    std::vector<Frame> frames;
//};

namespace
{
    void parseFrames(nlohmann::json json,
                     Texture2Handle texture,
                     SpriteSheet2::FrameMap& frames)
    {
        for(nlohmann::json::iterator it = json.begin(); it != json.end(); it++)
        {
            nlohmann::json value = it.value();
            I32 x = value["frame"]["x"];
            I32 y = value["frame"]["y"];
            I32 w = value["frame"]["w"];
            I32 h = value["frame"]["h"];

            SpriteSheet2::Frame frame;
            frame.pixInfo = glm::vec4(x, y, w, h);
            frame.texInfo = frame.pixInfo;
            frame.texInfo.x /= texture->width();
            frame.texInfo.y /= texture->height();
            frame.texInfo.z /= texture->width();
            frame.texInfo.w /= texture->height();

            std::string name = it.key();
            frames[name] = frame;
        }
    }

    void parseSequences(nlohmann::json json,
                         const SpriteSheet2::FrameMap& frames,
                         SpriteSheet2::SequenceMap& sequences)
    {
        for(nlohmann::json::iterator it = json.begin(); it != json.end(); it++)
        {
            nlohmann::json value = it.value();
            bool flip_horizontal = value["flip_horizontal"];
            I32 milliseconds_per_frame = value["milliseconds_per_frame"];
            std::vector<std::string> frameNames = value["frames"];

            SpriteSheet2::Sequence sequence;
            sequence.flipHorizontal = flip_horizontal;
            sequence.millisecondsPerFrame = milliseconds_per_frame;

            sequence.frames.reserve(frameNames.size());
            for(auto frameNames_it = frameNames.begin(); frameNames_it != frameNames.end(); frameNames_it++)
            {
                auto it = frames.find(*frameNames_it);
                if(it != frames.end())
                {
                    sequence.frames.push_back(it->second);
                }
            }

            std::string name = it.key();
            sequences[name] = sequence;
        }
    }
}

SpriteSheet2Handle SpriteSheet2::load(const std::string& filepath, Assets* loader)
{
    std::string type;
    std::string dependencies_texture;
    Texture2Handle texture;
    SpriteSheet2::FrameMap frames;
    SpriteSheet2::SequenceMap sequences;

    try
    {
        std::ifstream ifs(loader->assetDirectory() + filepath);
        nlohmann::json json;
        ifs >> json;

        type = json["type"];

        if(type != "SpriteSheet")
        {
            throw std::invalid_argument("Type is not SpriteSheet: " + filepath);
        }

        dependencies_texture = json["dependencies"]["texture"];

        texture = loader->get<Texture2>(dependencies_texture);

        if(!texture)
        {
            throw std::invalid_argument("Could not load Texture for SpriteSheet: " + dependencies_texture);
        }

        parseFrames(json["frames"], texture, frames);
        parseSequences(json["animations"], frames, sequences);
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("Failed to load SpriteSheet: %s", e.what());
        return SpriteSheet2Handle();
    }

    SpriteSheet2Handle handle(new SpriteSheet2());

    handle->_texture = texture;
    handle->_frames = frames;       //TODO: std::move?
    handle->_sequences = sequences; //TODO: std::move?

    return handle;
}
