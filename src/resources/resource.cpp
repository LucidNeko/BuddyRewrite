#include "resource.h"

#include "resources/resourcelocator.h"

Resource::Resource(std::string name)
    :_name(name)
{
}

Resource::~Resource()
{
}

std::string Resource::name() const
{
    return _name;
}
