#include "resources/resourcelocator.h"

ResourceLocator::ResourceLocator(Resource::Type type, std::string name)
    : _type(type),
      _name(name)
{
}

Resource::Type ResourceLocator::type() const
{
    return _type;
}

std::string ResourceLocator::name() const
{
    return _name;
}

bool ResourceLocator::operator==(const ResourceLocator& other) const
{
    return _type == other._type &&
           _name == other._name;
}
