#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "component.h"
#include "types.h"

class ComponentFactory
{
public:
    ComponentFactory();
    ~ComponentFactory();

    template<typename T>
    std::shared_ptr<T> create(EntityHandle entity) const
    {
        return std::make_shared<T>(entity);
    }

    ComponentHandle create(Component::Type type, EntityHandle entity) const;
};

#endif // COMPONENTFACTORY_H
