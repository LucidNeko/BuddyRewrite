#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "components/component.h"
#include "types.h"

class EntityFactory
{
public:
    static EntityHandle create();

private:
    static U64 _id;
};

#endif // ENTITYFACTORY_H
