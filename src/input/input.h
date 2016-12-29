#ifndef INPUT_H
#define INPUT_H

#include <vector>

#include "input/gamepad.h"
#include "input/keyboard.h"
#include "input/mouse.h"

class Input
{
public:
    Input(const Keyboard& keyboard,
          const Mouse& mouse,
          const std::vector<Gamepad>& gamepads);

    const Gamepad& gamepad(size_t index) const;
    const Keyboard& keyboard() const;
    const Mouse& mouse() const;

private:
    Keyboard _keyboard;
    Mouse _mouse;
    std::vector<Gamepad> _gamepads;
};

#endif // INPUT_H
