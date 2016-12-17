#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <unordered_map>
#include <unordered_set>

#include "types.h"

class Gamepad
{
public:
    enum class Button
    {
    };

    enum class Axis
    {
    };

public:
    Gamepad();
    Gamepad(std::unordered_set<I32> buttons,
            std::unordered_map<I32, F32> axisMap,
            Gamepad previous = Gamepad());
    Gamepad(const Gamepad& source);

    bool isButtonDown(I32 button) const;
    bool isButtonDownOnce(I32 button) const;

    F32 getAxis(I32 axis) const;

private:
    std::unordered_set<I32> _buttons;
    std::unordered_set<I32> _buttonsOnce;

    std::unordered_map<I32, F32> _axisMap;
};

class GamepadWatcher
{
public:
    virtual Gamepad state() const = 0;
};

#endif // GAMEPAD_H
