#include "input/keyboard.h"


bool Keyboard::isKeyDown(I32 key) const
{
    return _keys.find(key) != _keys.end();
}

bool Keyboard::isKeyDownOnce(I32 key) const
{
    return _keysOnce.find(key) != _keysOnce.end();
}
