#include "resources/spritesheet.h"

#include <fstream>
#include <sstream>

#include "json.hpp"

#include "utilities/io/io.h"
#include "resources/io/resources.h"
#include "resources/jsonfile.h"
#include "services.h"
#include "texture.h"
#include "logging.h"


SpriteSheet::SpriteSheet(std::string name)
    : Texture(name)
{
}

SpriteSheet::~SpriteSheet()
{
}

bool SpriteSheet::load()
{
    Texture::load();

    Services::get<Resources>()->load<JsonFile>("data/textures/" + Resource::name() + ".config");
    JsonFileHandle handle = Services::get<Resources>()->get<JsonFile>("data/textures/" + Resource::name() + ".config");

    if(handle)
    {
        const nlohmann::json& json = handle->json();

        _info = { json["frameWidth"],
                  json["frameHeight"],
                  json["rows"],
                  json["columns"],
                  json["fps"] };

        return true;
    }

    return false;
}

void SpriteSheet::destroy()
{
    Texture::destroy();
}

SpriteSheet::Info SpriteSheet::info() const
{
    return _info;
}
