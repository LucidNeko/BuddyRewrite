#include "assets/assets.h"

#include <fstream>
#include <sstream>

#include "json.hpp"

// Assets
#include "assets/asset.h"
#include "assets/shaderprogram.h"
#include "assets/texture.h"
#include "assets/spritesheet.h"

#include "logging.h"

Assets::Assets()
    : _assetDirectory("assets/")
{
    setLoader<ShaderProgram>(ShaderProgram::load);
    setLoader<Texture>(Texture::load);
    setLoader<SpriteSheet>(SpriteSheet::load);
}

Assets::~Assets()
{
}

void Assets::setAssetDirectory(const std::string& directory)
{
    _assetDirectory = directory;
}

const std::string& Assets::assetDirectory() const
{
    return _assetDirectory;
}

void Assets::freeUnreferencedResources()
{
    for(auto collection_it = _assets.begin(); collection_it != _assets.end();)
    {
        AssetCollection& collection = collection_it->second;

        for(auto asset_it = collection.begin(); asset_it != collection.end();)
        {
            // Reference to the handle to not mess with use_count.
            const AssetHandle& asset = asset_it->second;

            // If we hold the only reference, unload the asset.
            if(asset.use_count() == 1)
            {
                // Destructor will be called after erase.
                asset_it = collection.erase(asset_it);
            }
            else
            {
                asset_it++;
            }
        }

        // If the AssetCollection is now empty too, remove it.
        if(collection.empty())
        {
            collection_it = _assets.erase(collection_it);
        }
        else
        {
            collection_it++;
        }
    }
}

void Assets::setLoader(std::type_index type, LoaderFunction loader)
{
    _loaders[type] = loader;
}
bool Assets::load(std::type_index type, const std::string& name)
{
    if(isLoaded(type, name)) { return true; }

    auto it = _loaders.find(type);
    if(it != _loaders.end())
    {
        if(AssetHandle asset = it->second(name, this))
        {
            _assets[type][name] = asset;
            return true;
        }
    }
    LOG_ERROR("Failed to load asset: %s", name.c_str());
    return false;
}

bool Assets::isLoaded(std::type_index type, const std::string& name)
{
    const AssetCollection& assets = _assets[type];

    if(!assets.empty())
    {
        auto it = assets.find(name);
        if(it != assets.end())
        {
            return true;
        }
    }
    return false;
}

AssetHandle Assets::get(std::type_index type, const std::string& name)
{
    if(!isLoaded(type, name))
    {
        load(type, name);
    }

    const AssetCollection& assets = _assets[type];

    if(!assets.empty())
    {
        auto it = assets.find(name);
        if(it != assets.end())
        {
            return it->second;
        }
    }
    LOG_ERROR("Failed to get asset: %s", name.c_str());
    return AssetHandle();
}

