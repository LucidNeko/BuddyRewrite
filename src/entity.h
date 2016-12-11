#ifndef ENTITY_H
#define ENTITY_H

#include "types.h"

#include <memory>
#include <vector>

#include "assets/asset.h"
#include "components/component.h"
#include "components/componentcontainer.h"
#include "types.h"

class Entity : public Asset, public std::enable_shared_from_this<Entity>
{
public:
    static EntityHandle load(const std::string& filename, AssetsHandle assets);

public:
    Entity(U64 id);
    ~Entity();

    U64 id() const;

    template<typename T>
    std::shared_ptr<T> addComponent()
    {
        std::shared_ptr<T> component = std::make_shared<T>(shared_from_this());
        _components.add(component);
        return component;
    }

    template<typename T>
    std::shared_ptr<T> getComponent()
    {
        return _components.get<T>();
    }

    template<typename T>
    std::vector<std::shared_ptr<T> > getComponents()
    {
        return _components.getAll<T>();
    }

private:
    U64 _id;

    ComponentContainer _components;
};

#endif // ENTITY_H
