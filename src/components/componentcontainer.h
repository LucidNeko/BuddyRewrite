#ifndef COMPONENTCONTAINER_H
#define COMPONENTCONTAINER_H

#include <algorithm>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "types.h"

class ComponentContainer
{
private:
    typedef std::unordered_map<std::type_index, std::vector<ComponentHandle > > Map;

public:
    ~ComponentContainer() = default;

    template<typename Kind>
    void add(std::shared_ptr<Kind> item)
    {
        auto key = std::type_index(typeid(Kind));
        _map[key].push_back(item);
    }

    template<typename Kind>
    std::shared_ptr<Kind> get()
    {
        auto key = std::type_index(typeid(Kind));
        Map::const_iterator it = _map.find(key);
        if(it != _map.end() && !it->second.empty())
        {
            return std::static_pointer_cast<Kind>(it->second.front());
        }
        return std::shared_ptr<Kind>();
    }

    template<typename Kind>
    std::vector<std::shared_ptr<Kind> > getAll()
    {
        auto key = std::type_index(typeid(Kind));
        Map::const_iterator it = _map.find(key);
        if(it != _map.end() && !it->second.empty())
        {
            std::vector<std::shared_ptr<Kind> > out;
            out.resize(it->second.size());

            std::transform(std::begin(it->second), std::end(it->second), std::begin(out),
                [](auto& item){ return std::dynamic_pointer_cast<Kind>(item); });

            return out;
        }
        return std::vector<std::shared_ptr<Kind> >();
    }

private:
    Map _map;
};

#endif // COMPONENTCONTAINER_H
