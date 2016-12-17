#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <unordered_map>
#include <unordered_set>

#include "types.h"

class Gamepad
{
public:
    enum class Button {
        // Same as Qt values
        Invalid = -1,
        A = 0,
        B,
        X,
        Y,
        L1,
        R1,
        L2,
        R2,
        Select,
        Start,
        L3,
        R3,
        Up,
        Down,
        Right,
        Left,
        Center,
        Guide
    };

    enum class Axis {
        // Same as Qt values
        Invalid = -1,
        LeftX = 0,
        LeftY,
        RightX,
        RightY,
        // Extra because L2/R2 behave like axis
        L2,
        R2
    };

public:
    Gamepad();
    Gamepad(std::unordered_set<Button> buttons,
            std::unordered_map<Axis, F32> axisMap,
            Gamepad previous = Gamepad());
    Gamepad(const Gamepad& source);

    bool isButtonDown(Button button) const;
    bool isButtonDownOnce(Button button) const;

    F32 getAxis(Axis axis) const;

private:
    std::unordered_set<Button> _buttons;
    std::unordered_set<Button> _buttonsOnce;

    std::unordered_map<Axis, F32> _axisMap;
};

class GamepadWatcher
{
public:
    virtual Gamepad state() const = 0;
};

#endif // GAMEPAD_H
