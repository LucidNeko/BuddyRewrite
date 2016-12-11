#include "assets/entity.h"

#include <stdexcept>

#include "json.hpp"

#include "assets/assets.h"
#include "jsonutil.h"
#include "logging.h"
#include "uuid.h"

EntityHandle Entity::load(const std::string& filename, AssetsHandle assets)
{
    const std::string configFile = "/entity.json";
    std::string fullpath(assets->assetDirectory() + filename + configFile);

    std::string asset_type;
    std::string id;
    std::vector<std::string> components;

    try
    {
        JsonUtil jsonUtil;

        nlohmann::json json;
        jsonUtil.loadOrThrow(fullpath, json);

        asset_type = json["asset_type"];
        id = json["id"];
        components = json["components"];
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("Failed to load Entity: %s", e.what());
        return EntityHandle();
    }

    EntityHandle entity = std::make_shared<Entity>(Uuid(id));

    for(const std::string& component_name : components)
    {
        if(ComponentHandle component = assets->get<Component>(filename + component_name))
        {
            entity->addComponent(component);
        }
    }

    return entity;
}
