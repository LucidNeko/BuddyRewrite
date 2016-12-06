#include "filebackedresources.h"

#include <algorithm>

#include <QImage>

#include "logging.h"
#include "resources/texture.h"

FileBackedResources::FileBackedResources(std::string assetDirectory)
    : _assetDirectory(assetDirectory)
{
}

FileBackedResources::~FileBackedResources()
{
}

bool FileBackedResources::contains(ResourceLocator locator)
{
    return _resources.find(locator) != _resources.end();
}

void FileBackedResources::unloadFreeResources()
{
    for(auto it = std::begin(_resources); it != std::end(_resources);)
    {
        const std::shared_ptr<Resource>& resource = it->second;
        if(resource.use_count() == 1)
        {
            // The only instance is held by the resource manager.
            LOG_INFO("Removing \"%s\" because use_count=%d", resource->name().c_str(), resource.use_count() - 1);
            it->second->destroy();
            it = _resources.erase(it);
        }
        else
        {
//            LOG_INFO("Not removing \"%s\" because use_count=%d", resource->name().c_str(), resource.use_count());
            it++;
        }
    }
}

U32 FileBackedResources::useCount(ResourceLocator locator)
{
    auto it = _resources.find(locator);
    if(it != _resources.end())
    {
        // -1 because we hold on to one internally.
        return it->second.use_count() - 1;
    }
    return 0;
}
