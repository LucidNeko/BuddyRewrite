#include "input/input.h"

#include "logging.h"

Input::Input(const Keyboard& keyboard, const Mouse& mouse, const std::vector<Gamepad>& gamepads)
    : _keyboard(keyboard),
      _mouse(mouse),
      _gamepads(gamepads)
{
}

const Gamepad& Input::gamepad(size_t index) const
{
    if(index < _gamepads.size())
    {
        return _gamepads[index];
    }

    LOG_WARN("Gamepad %d is out of bounds", index);
    static Gamepad none;
    return none;
}

const Keyboard& Input::keyboard() const
{
    return _keyboard;
}

const Mouse& Input::mouse() const
{
    return _mouse;
}
