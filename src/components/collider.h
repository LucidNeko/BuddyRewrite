#ifndef COLLIDER_H
#define COLLIDER_H

#include "component.h"

class Collider : public Component
{
public:
    Collider(EntityHandle entity = nullptr);
    ~Collider();

    Type type() const override;
};

#endif // COLLIDER_H
