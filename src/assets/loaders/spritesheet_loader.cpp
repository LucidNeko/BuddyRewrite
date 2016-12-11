#include "assets/spritesheet.h"

#include <stdexcept>
#include <fstream>

#include "json.hpp"

#include "assets/assets.h"
#include "assets/texture.h"
#include "jsonutil.h"

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

            glm::vec4 pixelInfo = glm::vec4(x, y, w, h);
            glm::vec4 textureCoordInfo = pixelInfo;
            textureCoordInfo.x = textureCoordInfo.x / texture->width();
            textureCoordInfo.y = textureCoordInfo.y / texture->height();
            textureCoordInfo.z = textureCoordInfo.x + textureCoordInfo.z / texture->width();
            textureCoordInfo.w = textureCoordInfo.y + textureCoordInfo.w / texture->height();

            std::string name = it.key();
            frames[name] = SpriteSheetFrame(pixelInfo, textureCoordInfo);
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

            std::vector<SpriteSheetFrame> frameList;
            frameList.reserve(frameNames.size());
            for(auto frameNames_it = frameNames.begin(); frameNames_it != frameNames.end(); frameNames_it++)
            {
                auto it = frames.find(*frameNames_it);
                if(it != frames.end())
                {
                    frameList.push_back(it->second);
                }
            }

            std::string name = it.key();
            sequences[name] = SpriteSheetSequence(frameList,
                                                  milliseconds_per_frame,
                                                  flip_horizontal);
        }
    }
}

SpriteSheetHandle SpriteSheet::load(const std::string& filepath, AssetsHandle loader)
{
    const std::string configFile = "/spritesheet.json";
    std::string fullpath(loader->assetDirectory() + filepath + configFile);

    std::string config_asset_type;
    std::string config_texture;
    std::string config_frames;
    std::string config_sequences;

    TextureHandle texture;
    SpriteSheet::FrameMap frames;
    SpriteSheet::SequenceMap sequences;

    try
    {
        JsonUtil jsonUtil;

        nlohmann::json json;
        jsonUtil.loadOrThrow(fullpath, json);

        config_asset_type = json["asset_type"];
        config_texture = json["texture"];
        config_frames = json["frames"];
        config_sequences = jsonUtil.get<std::string>(json, {"sequences"});

        texture = loader->get<Texture>(config_texture);

        if(!texture)
        {
            throw std::invalid_argument("Could not load Texture for SpriteSheet: " + config_texture);
        }

        nlohmann::json frames_json;
        jsonUtil.loadOrThrow(loader->assetDirectory() + config_frames, frames_json);

        parseFrames(frames_json["frames"], texture, frames);

        if(!config_sequences.empty())
        {
            nlohmann::json animations_json;
            jsonUtil.loadOrThrow(loader->assetDirectory() + config_sequences, animations_json);

            parseSequences(animations_json["sequences"], frames, sequences);
        }
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
