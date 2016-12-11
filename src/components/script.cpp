#include "script.h"


Script::Script(EntityHandle entity)
    : Component(entity)
{

}

Script::~Script()
{

}

std::type_index Script::type() const
{
    return std::type_index(typeid(Script));
}
