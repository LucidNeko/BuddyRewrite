#include "components/componentcontainer.h"

#include "assets/component.h"

void ComponentContainer::add(ComponentHandle component)
{
    add(component->type(), component);
}

void ComponentContainer::add(std::type_index type, ComponentHandle component)
{
    _map[type].push_back(component);
}

ComponentHandle ComponentContainer::get(std::type_index type)
{
    auto it = _map.find(type);
    if(it != _map.end() && !it->second.empty())
    {
        return it->second.front();
    }
    return ComponentHandle();
}

const std::vector<ComponentHandle>& ComponentContainer::getAll(std::type_index type)
{
    auto it = _map.find(type);
    if(it != _map.end())
    {
        return it->second;
    }
    return std::vector<ComponentHandle>();
}
