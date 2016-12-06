#ifndef RESOURCES_H
#define RESOURCES_H

#include <memory>
#include <string>

#include "resources/io/filebackedresources.h"
#include "types.h"

class Resources
{
public:
    Resources();
    ~Resources() = default;

    template<typename T>
    void load(std::string name)
    {
        _d->load<T>(name);
    }

    template<typename T>
    std::shared_ptr<T> get(std::string name)
    {
        return _d->get<T>(name);
    }

    template<typename T>
    void unload(std::string name)
    {
        _d->unload<T>(name);
    }

    void unloadFreeResources();

    template<typename T>
    U32 useCount(std::string name)
    {
        return _d->useCount<T>(name);
    }

private:
    std::unique_ptr<FileBackedResources> _d;
};

#endif // RESOURCES_H
