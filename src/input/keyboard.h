#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <unordered_set>

#include "types.h"

class Keyboard
{
public:
    bool isKeyDown(I32 key) const;
    bool isKeyDownOnce(I32 key) const;

private:
    std::unordered_set<I32> _keys;
    std::unordered_set<I32> _keysOnce;

    friend class InputSystem;
};

#endif // KEYBOARD_H
