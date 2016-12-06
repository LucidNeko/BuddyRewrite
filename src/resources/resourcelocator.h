#ifndef RESOURCELOCATOR_H
#define RESOURCELOCATOR_H

#include <string>

#include "resources/resource.h"

class ResourceLocator
{
public:
    ResourceLocator(Resource::Type type = Resource::TYPE_NULL, std::string name = "");
    ~ResourceLocator() = default;

    Resource::Type type() const;
    std::string name() const;

    bool operator==(const ResourceLocator& other) const;

private:
    Resource::Type _type;
    std::string _name;
};

/**
 * Hash Function.
 */
namespace std
{
    template<>
    struct hash<ResourceLocator>
    {
        std::size_t operator()(const ResourceLocator& value) const
        {
            const std::size_t prime = 31;
            std::size_t result = 1;
            result = prime * result + hash<string>()(value.name());
            result = prime * result + hash<std::size_t>()(static_cast<std::size_t>(value.type()));
            return result;
        }
    };
}

#endif // RESOURCELOCATOR_H
