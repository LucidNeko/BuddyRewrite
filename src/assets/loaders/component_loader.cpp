#include "assets/component.h"

#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "json.hpp"

// Components
#include "components/animation.h"
#include "components/collider.h"
#include "components/rigidbody.h"
#include "components/script.h"
#include "components/sprite.h"
#include "components/transform.h"

// Scripts
#include "scripts/testscript.h"

#include "assets/assets.h"
#include "assets/spritesheet.h"
#include "assets/entity.h"
#include "jsonutil.h"
#include "logging.h"

namespace
{
    bool setup(std::shared_ptr<Animation> animation, nlohmann::json& json, AssetsHandle assets)
    {
        std::string spritesheet_file = json["spritesheet"];
        std::string sequence_name = json["sequence"];

        if(SpriteSheetHandle spritesheet = assets->get<SpriteSheet>(spritesheet_file))
        {
            SpriteSheetSequence sequence;
            if(spritesheet->sequence(sequence_name, sequence))
            {
                animation->setSequence(sequence);
            }
        }

        return true;
    }

    bool setup(std::shared_ptr<Collider>, nlohmann::json&, AssetsHandle)
    {
        return true;
    }

    bool setup(std::shared_ptr<RigidBody>, nlohmann::json&, AssetsHandle)
    {
        return true;
    }

    bool setup(std::shared_ptr<Sprite> sprite, nlohmann::json& json, AssetsHandle assets)
    {
        JsonUtil jsonUtil;

        std::string spritesheet = json["spritesheet"];
        std::string frame_name = jsonUtil.get<std::string>(json, {"frame"});

        I32 w = jsonUtil.get(json, {"size", "w"});
        I32 h = jsonUtil.get(json, {"size", "h"});

        SpriteSheetHandle spritesheet_handle = assets->get<SpriteSheet>(spritesheet);
        sprite->setSpriteSheet(spritesheet_handle);
        sprite->setSize(glm::vec2(w, h));

        if(spritesheet_handle && !frame_name.empty())
        {
            SpriteSheetFrame frame;
            if(spritesheet_handle->frame(frame_name, frame))
            {
                sprite->setCurrentFrame(frame);
            }
        }

        return true;
    }

    bool setup(std::shared_ptr<Transform> transform, nlohmann::json& json, AssetsHandle)
    {
        JsonUtil jsonUtil;

        I32 x = jsonUtil.get(json, {"position", "x"});
        I32 y = jsonUtil.get(json, {"position", "y"});

        transform->setPosition(glm::vec2(x, y));

        return true;
    }

    bool setup(std::shared_ptr<TestScript>, nlohmann::json&, AssetsHandle)
    {
        return true;
    }

    bool setupComponent(std::shared_ptr<Component> component, nlohmann::json& json, AssetsHandle assets)
    {
        // Components
        if(std::shared_ptr<Animation> subtype = std::dynamic_pointer_cast<Animation>(component))
        {
            return setup(subtype, json, assets);
        }
        else if(std::shared_ptr<Collider> subtype = std::dynamic_pointer_cast<Collider>(component))
        {
            return setup(subtype, json, assets);
        }
        else if(std::shared_ptr<RigidBody> subtype = std::dynamic_pointer_cast<RigidBody>(component))
        {
            return setup(subtype, json, assets);
        }
        else if(std::shared_ptr<Sprite> subtype = std::dynamic_pointer_cast<Sprite>(component))
        {
            return setup(subtype, json, assets);
        }
        else if(std::shared_ptr<Transform> subtype = std::dynamic_pointer_cast<Transform>(component))
        {
            return setup(subtype, json, assets);
        }

        // Scripts
        if(std::shared_ptr<TestScript> subtype = std::dynamic_pointer_cast<TestScript>(component))
        {
            return setup(subtype, json, assets);
        }

        return false;
    }
}

ComponentHandle Component::load(const std::string& filename, AssetsHandle assets)
{
    std::string fullpath(assets->assetDirectory() + filename);

    try
    {
        JsonUtil jsonUtil;

        nlohmann::json json;
        jsonUtil.loadOrThrow(fullpath, json);

        std::string asset_type = json["asset_type"];

        ComponentHandle component = Component::create(asset_type);

        if(!setupComponent(component, json, assets))
        {
            throw std::invalid_argument("Could not setup Component: " + asset_type);
        }

        return component;
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("Failed to load Component: %s", e.what());
        return nullptr;
    }
}
