#include "assets/spritesheet2.h"

#include <fstream>

#include "json.hpp"

#include "assets/assets.h"
#include "assets/texture2.h"

#include "logging.h"

namespace
{
    void parseFrames(nlohmann::json json,
                     TextureHandle texture,
                     SpriteSheet::FrameMap& frames)
    {
        for(nlohmann::json::iterator it = json.begin(); it != json.end(); it++)
        {
            nlohmann::json value = it.value();
            I32 x = value["frame"]["x"];
            I32 y = value["frame"]["y"];
            I32 w = value["frame"]["w"];
            I32 h = value["frame"]["h"];

            SpriteSheet::Frame frame;
            frame.pixInfo = glm::vec4(x, y, w, h);
            frame.texInfo = frame.pixInfo;
            frame.texInfo.x = frame.texInfo.x / texture->width();
            frame.texInfo.y = frame.texInfo.y / texture->height();
            frame.texInfo.z = frame.texInfo.x + frame.texInfo.z / texture->width();
            frame.texInfo.w = frame.texInfo.y + frame.texInfo.w / texture->height();

            std::string name = it.key();
            frames[name] = frame;
        }
    }

    void parseSequences(nlohmann::json json,
                         const SpriteSheet::FrameMap& frames,
                         SpriteSheet::SequenceMap& sequences)
    {
        for(nlohmann::json::iterator it = json.begin(); it != json.end(); it++)
        {
            nlohmann::json value = it.value();
            bool flip_horizontal = value["flip_horizontal"];
            I32 milliseconds_per_frame = value["milliseconds_per_frame"];
            std::vector<std::string> frameNames = value["frames"];

            SpriteSheet::Sequence sequence;
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

SpriteSheetHandle SpriteSheet::load(const std::string& filepath, Assets* loader)
{
    std::string type;
    std::string dependencies_texture;
    std::string dependencies_definition;
    TextureHandle texture;
    SpriteSheet::FrameMap frames;
    SpriteSheet::SequenceMap sequences;

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

        texture = loader->get<Texture>(dependencies_texture);

        if(!texture)
        {
            throw std::invalid_argument("Could not load Texture for SpriteSheet: " + dependencies_texture);
        }

        dependencies_definition = json["dependencies"]["definition"];

        std::ifstream definition_ifs(loader->assetDirectory() + dependencies_definition);
        nlohmann::json definition_json;
        definition_ifs >> definition_json;

        parseFrames(definition_json["frames"], texture, frames);
        parseSequences(json["animations"], frames, sequences);
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("Failed to load SpriteSheet: %s", e.what());
        return SpriteSheetHandle();
    }

    SpriteSheetHandle handle(new SpriteSheet());

    handle->_texture = texture;
    handle->_frames = frames;       //TODO: std::move?
    handle->_sequences = sequences; //TODO: std::move?

    return handle;
}
