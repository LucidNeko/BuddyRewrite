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

    void add(ComponentHandle component);

    template<typename T>
    void add(std::shared_ptr<T> component)
    {
        add(std::type_index(typeid(T)), component);
    }

    template<typename T>
    std::shared_ptr<T> get()
    {
        return std::dynamic_pointer_cast<T>(get(std::type_index(typeid(T))));
    }

    template<typename T>
    std::vector<std::shared_ptr<T> > getAll()
    {
        const std::vector<ComponentHandle>& all = getAll(std::type_index(typeid(T)));

        std::vector<std::shared_ptr<T> > out;
        out.resize(all.size());

        std::transform(std::begin(all), std::end(all), std::begin(out),
            [](auto& item){ return std::dynamic_pointer_cast<T>(item); });

        return out;
    }

private:
    void add(std::type_index type, ComponentHandle component);
    ComponentHandle get(std::type_index type);
    const std::vector<ComponentHandle>& getAll(std::type_index type);

private:
    Map _map;
};

#endif // COMPONENTCONTAINER_H
