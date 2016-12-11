#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/vec2.hpp>

#include "component.h"
#include "types.h"

class Transform : public Component
{
public:
    Transform(EntityHandle entity = nullptr);
    ~Transform();

    std::type_index type() const override;

    glm::vec2 position() const;
    void setPosition(glm::vec2 position);

    glm::vec2 scale() const;
    void setScale(glm::vec2 scale);

    Angle rotation() const;
    void setRotation(Angle rotation);

private:
    glm::vec2 _position;
    glm::vec2 _scale;
    Angle     _rotation;
};

#endif // TRANSFORM_H
