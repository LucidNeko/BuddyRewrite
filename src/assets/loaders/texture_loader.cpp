#include "assets/texture.h"

#include <stdexcept>
#include <fstream>

#include "stb_image.h"

#include "json.hpp"

#include "assets/assets.h"
#include "jsonutil.h"
#include "logging.h"

TextureHandle Texture::load(const std::string& filepath, Assets* loader)
{
    const std::string configFile = "/texture.json";
    std::string fullpath(loader->assetDirectory() + filepath + configFile);

    std::string asset_type = "";
    std::string image_path = "";
    bool has_alpha = false;

    U8* image_data = nullptr;
    I32 image_width = 0;
    I32 image_height = 0;
    I32 image_channels = 0;

    try
    {
        JsonUtil jsonUtil;

        nlohmann::json json;
        jsonUtil.loadOrThrow(fullpath, json);

        asset_type = json["asset_type"];
        image_path = json["image_path"];
        has_alpha = json["has_alpha"];

        std::string image_fullpath = loader->assetDirectory() + image_path;
        I32 desired_channels = has_alpha ? STBI_rgb_alpha : STBI_rgb;

        image_data = stbi_load(image_fullpath.c_str(), &image_width, &image_height, &image_channels, desired_channels);
        if(!image_data)
        {
            throw std::invalid_argument("Could not load image from: " + image_fullpath);
        }
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("Failed to load texture: %s", e.what());
        return TextureHandle();
    }

    TextureHandle handle(new Texture());

    handle->_width = image_width;
    handle->_height = image_height;

    const I32 byteCount = image_width * image_height * image_channels;

    handle->_data.reserve(byteCount);
    handle->_data = std::vector<GLubyte>(image_data, image_data + byteCount);

    stbi_image_free(image_data);

    handle->create();

    return handle;
}
