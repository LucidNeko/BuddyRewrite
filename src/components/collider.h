#ifndef COLLIDER_H
#define COLLIDER_H

#include "component.h"

class Collider : public Component
{
public:
    Collider(EntityHandle entity = nullptr);
    ~Collider();

    std::type_index type() const override;
};

#endif // COLLIDER_H
