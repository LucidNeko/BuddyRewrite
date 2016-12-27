#include "assets/scene.h"

#include <stdexcept>
#include <vector>

#include "json.hpp"

#include "assets/assets.h"
#include "assets/spritesheet.h"
#include "assets/texture.h"
#include "assets/entity.h"
#include "jsonutil.h"
#include "logging.h"

SceneHandle Scene::load(const std::string& filepath, AssetsHandle loader)
{
    const std::string configFile = "/scene.json";
    std::string fullpath(loader->assetDirectory() + filepath + configFile);

    std::string asset_type;
    std::vector<std::string> entities;

    try
    {
        JsonUtil jsonUtil;

        nlohmann::json json;
        jsonUtil.loadOrThrow(fullpath, json);

        asset_type = json["asset_type"];

        nlohmann::json asset_dependencies = json["asset_dependencies"];
        for(nlohmann::json object : asset_dependencies)
        {
            std::string dependency_type = object["asset_type"];
            std::string dependency_file = object["asset"];

            //TODO: Get rid of if/else chain.
            if(dependency_type == "SpriteSheet")
            {
                loader->load<SpriteSheet>(dependency_file);
            }
            else if(dependency_type == "Texture")
            {
                loader->load<Texture>(dependency_file);
            }
        }

        for(const nlohmann::json& obj : json["entities"])
        {
            entities.push_back(obj);
        }
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("Failed to load scene: %s", e.what());
        return SceneHandle();
    }

    SceneHandle scene = SceneHandle(new Scene(loader));

    for(const std::string& entity : entities)
    {
        scene->add(loader->get<Entity>(entity));
    }

    return scene;
}
