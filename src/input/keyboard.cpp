#include "input/keyboard.h"


Keyboard::Keyboard()
{
}

Keyboard::Keyboard(std::unordered_set<I32> keys, Keyboard previous)
    : _keys(keys)
{
    for(I32 key : _keys)
    {
        if(!previous.isKeyDown(key))
        {
            _keysOnce.insert(key);
        }
    }
}

Keyboard::Keyboard(const Keyboard& source)
    : _keys(source._keys),
      _keysOnce(source._keysOnce)
{
}

bool Keyboard::isKeyDown(I32 key) const
{
    return _keys.find(key) != _keys.end();
}

bool Keyboard::isKeyDownOnce(I32 key) const
{
    return _keysOnce.find(key) != _keysOnce.end();
}
