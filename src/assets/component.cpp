#include "assets/component.h"

#include <unordered_map>

#include "logging.h"

// Components.
#include "components/animation.h"
#include "components/collider.h"
#include "components/rigidbody.h"
#include "components/script.h"
#include "components/sprite.h"
#include "components/transform.h"

Component::Component(EntityHandle entity)
    : _entity(entity)
{
}

Component::~Component()
{
}

// TODO: Can't use typeName in the destructor because it calls type() on extended class.
std::string Component::typeName() const
{
    static std::unordered_map<std::type_index, std::string> typeNames({
        {std::type_index(typeid(class Collider )), "Collider"},
        {std::type_index(typeid(class RigidBody)), "RigidBody"},
        {std::type_index(typeid(class Sprite   )), "Sprite"},
        {std::type_index(typeid(class Transform)), "Transform"},
        {std::type_index(typeid(class Script   )), "Script"},
        {std::type_index(typeid(class Animation)), "Animation"}
    });

    auto it = typeNames.find(type());
    return (it != typeNames.end()) ? it->second : "Unknown";
}

EntityHandle Component::entity() const
{
    return _entity.lock();
}

void Component::setEntity(EntityHandle entity)
{
    _entity = entity;
}
