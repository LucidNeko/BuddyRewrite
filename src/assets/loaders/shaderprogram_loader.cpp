#include "assets/shaderprogram.h"

#include <stdexcept>
#include <string>

#include "json.hpp"

#include "assets/assets.h"
#include "jsonutil.h"

#include "logging.h"

ShaderProgramHandle ShaderProgram::load(const std::string& filepath, AssetsHandle loader)
{
    const std::string configFile = "/program.json";
    std::string fullpath(loader->assetDirectory() + filepath + configFile);

    std::string asset_type;
    std::string vertex_shader;
    std::string fragment_shader;

    try
    {
        JsonUtil jsonUtil;

        nlohmann::json json;
        jsonUtil.loadOrThrow(fullpath, json);

        asset_type = json["asset_type"];
        vertex_shader = json["vertex_shader"];
        fragment_shader = json["fragment_shader"];
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("Failed to load shader: %s", e.what());
        return ShaderProgramHandle();
    }

    ShaderProgramHandle handle(new ShaderProgram());

    handle->_vertextPath = loader->assetDirectory() + vertex_shader;
    handle->_fragmentPath = loader->assetDirectory() + fragment_shader;

    if(handle->reload())
    {
        return handle;
    }

    LOG_ERROR("Failed to load shader program: %s", fullpath);
    return ShaderProgramHandle();
}
