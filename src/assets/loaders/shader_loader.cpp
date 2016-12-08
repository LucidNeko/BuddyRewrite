#include "assets/shader.h"

#include <stdexcept>
#include <string>

#include "json.hpp"

#include "assets/assets.h"
#include "jsonutil.h"

#include "logging.h"

ShaderHandle Shader::load(const std::string& filepath, Assets* loader)
{
//    "type": "Shader",
//    "vertex_shader": "shaders/text/text.vert",
//    "fragment_shader": "shaders/text/text.frag"

    std::string type;
    std::string vertex_shader;
    std::string fragment_shader;

    JsonUtil jsonLoader;

    try
    {
        nlohmann::json json;
        jsonLoader.loadOrThrow(loader->assetDirectory() + filepath, json);

        type = json["type"];
        vertex_shader = json["vertex_shader"];
        fragment_shader = json["fragment_shader"];
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("Failed to load shader: %s", e.what());
        return ShaderHandle();
    }

    ShaderHandle handle;

    handle->_vertextPath = loader->assetDirectory() + vertex_shader;
    handle->_fragmentPath = loader->assetDirectory() + fragment_shader;

    if(handle->reload())
    {
        return handle;
    }

    LOG_ERROR("Failed to load shader: %s", filepath);
    return ShaderHandle();
}
