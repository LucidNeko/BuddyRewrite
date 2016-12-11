#include "assets/component.h"

#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "json.hpp"

#include "assets/assets.h"
#include "assets/spritesheet.h"
#include "components/transform.h"
#include "components/rigidbody.h"
#include "components/sprite.h"
#include "components/animation.h"
#include "assets/entity.h"
#include "jsonutil.h"
#include "logging.h"

namespace
{
    std::shared_ptr<Transform> loadTransform(nlohmann::json& json, AssetsHandle)
    {
        std::shared_ptr<Transform> transform(new Transform());

        JsonUtil jsonUtil;

        I32 x = jsonUtil.get(json, {"position", "x"});
        I32 y = jsonUtil.get(json, {"position", "y"});

        transform->setPosition(glm::vec2(x, y));

        return transform;
    }

    std::shared_ptr<RigidBody> loadRigidBody(nlohmann::json&, AssetsHandle)
    {
        std::shared_ptr<RigidBody> rigidBody(new RigidBody());

        return rigidBody;
    }

    std::shared_ptr<Sprite> loadSprite(nlohmann::json& json, AssetsHandle assets)
    {
        std::shared_ptr<Sprite> sprite(new Sprite());

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

        return sprite;
    }

    std::shared_ptr<Animation> loadAnimation(nlohmann::json& json, AssetsHandle assets)
    {
        std::shared_ptr<Animation> animation(new Animation());

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

        return animation;
    }
}


ComponentHandle Component::load(const std::string& filename, AssetsHandle assets)
{
    static std::unordered_map<std::string, std::function<ComponentHandle(nlohmann::json&, AssetsHandle)> > _loaders({
        {"Transform", loadTransform},
        {"RigidBody", loadRigidBody},
        {"Sprite",    loadSprite},
        {"Animation", loadAnimation}
    });

    std::string fullpath(assets->assetDirectory() + filename);

    try
    {
        JsonUtil jsonUtil;

        nlohmann::json json;
        jsonUtil.loadOrThrow(fullpath, json);

        std::string asset_type = json["asset_type"];

        auto it = _loaders.find(asset_type);
        if(it != _loaders.end())
        {
            return it->second(json, assets);
        }
        else
        {
            throw std::invalid_argument("No loader to handle Component: " + asset_type);
        }
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("Failed to load Component: %s", e.what());
        return ComponentHandle();
    }
}
