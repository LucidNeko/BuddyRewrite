#ifndef ENTITYCOLLECTION_H
#define ENTITYCOLLECTION_H

#include <vector>

#include "types.h"

class EntityCollection
{
public:
    EntityCollection();
    ~EntityCollection();

    bool add(EntityHandle entity);

    EntityHandle remove(U64 id);

    EntityHandle get(U64 id) const;

    std::vector<EntityHandle>& entities();

private:
    std::vector<EntityHandle> _entities;
};

#endif // ENTITYCOLLECTION_H
