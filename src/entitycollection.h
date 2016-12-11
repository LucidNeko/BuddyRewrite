#ifndef ENTITYCOLLECTION_H
#define ENTITYCOLLECTION_H

#include <vector>

#include "types.h"
#include "uuid.h"

class EntityCollection
{
public:
    EntityCollection();
    ~EntityCollection();

    bool add(EntityHandle entity);

    EntityHandle remove(Uuid id);

    EntityHandle get(Uuid id) const;

    std::vector<EntityHandle>& entities();

private:
    std::vector<EntityHandle> _entities;
};

#endif // ENTITYCOLLECTION_H
