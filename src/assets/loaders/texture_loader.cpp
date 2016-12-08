#include "assets/texture.h"

#include <stdexcept>
#include <fstream>

#include <QImage>

#include "json.hpp"

#include "assets/assets.h"
#include "jsonutil.h"
#include "logging.h"

TextureHandle Texture::load(const std::string& filepath, Assets* loader)
{
    QImage image;
    std::string type;
    std::string image_path;
    std::string format;
    U32 size_w;
    U32 size_h;

    JsonUtil jsonLoader;

    try
    {
        nlohmann::json json;
        jsonLoader.loadOrThrow(loader->assetDirectory() + filepath, json);

        type = json["type"];

        if(type != "Texture")
        {
            throw std::invalid_argument("Type is not Texture: " + filepath);
        }

        image_path = json["filepath"];
        format = json["format"];
        size_w = json["size"]["w"];
        size_h = json["size"]["h"];

        std::string image_fullpath = loader->assetDirectory() + image_path;
        image = QImage(image_fullpath.c_str());

        if(image.isNull())
        {
            throw std::invalid_argument("Could not load image from: " + image_fullpath);
        }

        if(image.width() != size_w || image.height() != size_h)
        {
            throw std::invalid_argument("Config size does not match image size: " + filepath);
        }

        image = image.convertToFormat(QImage::Format_RGBA8888);
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("Failed to load texture: %s", e.what());
        return TextureHandle();
    }

    TextureHandle handle(new Texture());

    handle->_width = size_w;
    handle->_height = size_h;

    const I32 byteCount = image.byteCount();
    const GLubyte* bytes = image.constBits();

    handle->_data.reserve(byteCount);
    handle->_data = std::vector<GLubyte>(bytes, bytes + byteCount);

    handle->create();

    return handle;
}
