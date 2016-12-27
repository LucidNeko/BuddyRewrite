#include "input/gamepad.h"

Gamepad::Gamepad()
{
}

Gamepad::Gamepad(std::unordered_set<Button, EnumClassHash> buttons, std::unordered_map<Axis, F32, EnumClassHash> axisMap, Gamepad previous)
    : _buttons(buttons),
      _axisMap(axisMap)
{
    for(Button button : _buttons)
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

bool Gamepad::isButtonDown(Button button) const
{
    return _buttons.find(button) != _buttons.end();
}

bool Gamepad::isButtonDownOnce(Button button) const
{
    return _buttonsOnce.find(button) != _buttonsOnce.end();
}

F32 Gamepad::getAxis(Axis axis) const
{
    auto it = _axisMap.find(axis);
    if(it != _axisMap.end())
    {
        return it->second;
    }
    return 0;
}
