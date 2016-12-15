#include "input/gamepad.h"


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
