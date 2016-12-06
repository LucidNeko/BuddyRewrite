#ifndef FILEBACKEDRESOURCES_H
#define FILEBACKEDRESOURCES_H

#include <memory>
#include <string>
#include <unordered_map>

#include "logging.h"
#include "resources/resource.h"
#include "resources/resourcelocator.h"
#include "types.h"

class FileBackedResources
{
public:
    FileBackedResources(std::string assetDirectory);
    ~FileBackedResources();

    template<typename T>
    void load(std::string name)
    {
        ResourceLocator locator(T::type(), name);

        if(!contains(locator))
        {
            ResourceHandle resource(new T(name));
            if(resource->load())
            {
                LOG_INFO("Loaded \"%s\"", resource->name().c_str());
                _resources[locator] = resource;
            }
            else
            {
                LOG_INFO("Failed to load \"%s\"", resource->name().c_str());
            }
        }
    }

    template<typename T>
    std::shared_ptr<T> get(std::string name)
    {
        ResourceLocator locator(T::type(), name);

        auto it = _resources.find(locator);
        if(it != _resources.end())
        {
            return std::static_pointer_cast<T>(it->second);
        }
        return std::shared_ptr<T>();
    }

    template<typename T>
    void unload(std::string name)
    {
        ResourceLocator locator(T::type(), name);

        auto it = _resources.find(locator);
        if(it != _resources.end())
        {
            LOG_INFO("unload \"%s\"", name.c_str());
            _it->second->destroy();
            _resources.erase(it);
        }
    }

    template<typename T>
    U32 useCount(std::string name)
    {
        ResourceLocator locator(T::type(), name);

        return useCount(locator);
    }

    U32 useCount(ResourceLocator locator);


    bool contains(ResourceLocator locator);

    void unloadFreeResources();

private:
    std::string _assetDirectory;

    std::unordered_map<ResourceLocator, std::shared_ptr<Resource> > _resources;
};

#endif // FILEBACKEDRESOURCES_H
