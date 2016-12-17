#include "input/gamepad.h"


Gamepad::Gamepad()
{
}

Gamepad::Gamepad(std::unordered_set<I32> buttons, std::unordered_map<I32, F32> axisMap, Gamepad previous)
    : _buttons(buttons),
      _axisMap(axisMap)
{
    for(I32 button : _buttons)
    {
        if(!previous.isButtonDown(button))
        {
            _buttonsOnce.insert(button);
        }
    }
}

Gamepad::Gamepad(const Gamepad& source)
    : _buttons(source._buttons),
      _buttonsOnce(source._buttonsOnce),
      _axisMap(source._axisMap)
{
}

bool Gamepad::isButtonDown(I32 button) const
{
    return _buttons.find(button) != _buttons.end();
}

bool Gamepad::isButtonDownOnce(I32 button) const
{
    return _buttonsOnce.find(button) != _buttonsOnce.end();
}

F32 Gamepad::getAxis(I32 axis) const
{
    auto it = _axisMap.find(axis);
    if(it != _axisMap.end())
    {
        return it->second;
    }
    return 0;
}
