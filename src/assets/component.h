#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <typeindex>
#include <typeinfo>

#include "assets/asset.h"
#include "types.h"

class Component : public Asset
{
public:
    static ComponentHandle load(const std::string& filename, AssetsHandle assets);

    template<typename T>
    static std::shared_ptr<T> create(std::string type)
    {
        return std::dynamic_pointer_cast<T>(create(type));
    }
    static ComponentHandle create(std::string type);

public:
    Component(EntityHandle entity = nullptr);
    virtual ~Component() {}

    virtual std::type_index type() const = 0;

    std::string typeName() const;

    EntityHandle entity() const;
    void setEntity(EntityHandle entity);

private:
    EntityWeakHandle _entity;
};

#endif // COMPONENT_H
