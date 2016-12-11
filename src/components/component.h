#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

#include "assets/asset.h"
#include "types.h"

class Component : Asset
{
public:
    enum Type
    {
        Collider,
        RigidBody,
        Sprite,
        SpriteRenderer,
        Transform,
        Script,
        Animation
    };

    static void load(EntityHandle entity, const std::string& filename, AssetsHandle assets);

public:
    Component(EntityHandle entity = nullptr);
    virtual ~Component();

    virtual Component::Type type() const = 0;

    const char* typeName() const;

    EntityHandle entity() const;

private:
    EntityWeakHandle _entity;
};

#endif // COMPONENT_H
