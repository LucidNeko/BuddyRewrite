#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <unordered_set>

#include "types.h"

class Keyboard
{
public:
    enum class Key
    {
    };

public:
    Keyboard();
    Keyboard(std::unordered_set<I32> keys,
             Keyboard previous = Keyboard());
    Keyboard(const Keyboard& source);

    bool isKeyDown(I32 key) const;
    bool isKeyDownOnce(I32 key) const;

private:
    std::unordered_set<I32> _keys;
    std::unordered_set<I32> _keysOnce;
};

class KeyboardWatcher
{
public:
    virtual Keyboard state() const = 0;
};

#endif // KEYBOARD_H
