#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

#include "types.h"

class Component
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

    static ComponentHandle load(EntityHandle entity, const std::string& filename, class Assets* assets);

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
