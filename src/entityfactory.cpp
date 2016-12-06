#include "entityfactory.h"

#include "entity.h"

U64 EntityFactory::_id = 0x0;

EntityHandle EntityFactory::create()
{
    return std::make_shared<Entity>(_id++);
}
