#include "input/keyboard.h"


Keyboard::Key Keyboard::keyFromQtKey(I32 key)
{
    return static_cast<Key>(key);
}

Keyboard::Keyboard()
{
}

Keyboard::Keyboard(std::unordered_set<Key> keys, Keyboard previous)
    : _keys(keys)
{
    for(Key key : _keys)
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

bool Keyboard::isKeyDown(Key key) const
{
    return _keys.find(key) != _keys.end();
}

bool Keyboard::isKeyDownOnce(Key key) const
{
    return _keysOnce.find(key) != _keysOnce.end();
}
