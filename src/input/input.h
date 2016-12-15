#ifndef INPUT_H
#define INPUT_H

#include <vector>

#include "input/gamepad.h"
#include "input/keyboard.h"
#include "input/mouse.h"
#include "types.h"

class Input
{
public:
    const Gamepad& gamepad(size_t index) const;
    const Keyboard& keyboard() const;
    const Mouse& mouse() const;

private:
    std::vector<Gamepad> _gamepads;
    Keyboard _keyboard;
    Mouse _mouse;

    friend class InputSystem;
};

#endif // INPUT_H
