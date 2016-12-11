#ifndef ENTITY_H
#define ENTITY_H

#include "types.h"

#include <algorithm>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "assets/asset.h"
#include "assets/component.h"
#include "logging.h"
#include "types.h"
#include "uuid.h"

class Entity : public Asset, public std::enable_shared_from_this<Entity>
{
public:
    static EntityHandle load(const std::string& filename, AssetsHandle assets);

public:
    Entity(Uuid id = Uuid());
    ~Entity();

    Uuid id() const;

    void addComponent(ComponentHandle component);

    template<typename T>
    std::shared_ptr<T> addComponent()
    {
        std::shared_ptr<T> component = std::make_shared<T>();
        addComponent(component);
        return component;
    }

    template<typename T>
    std::shared_ptr<T> getComponent()
    {
        std::type_index type(typeid(T));
        return std::dynamic_pointer_cast<T>(getComponent(type));
    }

    template<typename T>
    std::vector<std::shared_ptr<T> > getComponents()
    {
        std::type_index type(typeid(T));
        const std::vector<ComponentHandle>& all = getComponents(type);

        std::vector<std::shared_ptr<T> > out;
        out.resize(all.size());

        std::transform(std::begin(all), std::end(all), std::begin(out),
            [](auto& item){ return std::dynamic_pointer_cast<T>(item); });

        return out;
    }


private:
    ComponentHandle getComponent(std::type_index type);
    const std::vector<ComponentHandle>& getComponents(std::type_index type);

private:
    Uuid _id;

    std::unordered_map<std::type_index, std::vector<ComponentHandle > > _components;
};

#endif // ENTITY_H
