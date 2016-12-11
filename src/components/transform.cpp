#include "transform.h"

Transform::Transform(EntityHandle entity)
    : Component(entity),
      _position(0, 0),
      _scale(1, 1),
      _rotation(0)
{
}

Transform::~Transform()
{
}

std::type_index Transform::type() const
{
    return std::type_index(typeid(Transform));
}

glm::vec2 Transform::position() const
{
    return _position;
}

void Transform::setPosition(glm::vec2 position)
{
    _position = position;
}

glm::vec2 Transform::scale() const
{
    return _scale;
}

void Transform::setScale(glm::vec2 scale)
{
    _scale = scale;
}

Angle Transform::rotation() const
{
    return _rotation;
}

void Transform::setRotation(Angle rotation)
{
    _rotation = rotation;
}
