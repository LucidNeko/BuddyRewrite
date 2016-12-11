#ifndef ENTITY_H
#define ENTITY_H

#include "types.h"

#include <memory>
#include <vector>

#include "assets/asset.h"
#include "assets/component.h"
#include "components/componentcontainer.h"
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
        return _components.get<T>();
    }

    template<typename T>
    std::vector<std::shared_ptr<T> > getComponents()
    {
        return _components.getAll<T>();
    }

private:
    Uuid _id;

    ComponentContainer _components;
};

#endif // ENTITY_H
