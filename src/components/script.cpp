#include "script.h"


Script::Script(EntityHandle entity)
    : Component(entity)
{

}

Script::~Script()
{

}

Component::Type Script::type() const
{
    return Component::Script;
}
