#include "inputsystem.h"

#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QtGamepad/QGamepad>

#include "logging.h"

InputSystem::InputSystem()
    : QObject(nullptr)
{
    const I32 MAX_CONTROLLERS = 8;
    for(I32 i = 0; i < MAX_CONTROLLERS; i++)
    {
        _gamepads.push_back(std::make_shared<QGamepad>(i));
        hookup(_gamepads.back().get());
    }

    _state._gamepads.resize(MAX_CONTROLLERS);
    _lastState = _state;
}

InputSystem::~InputSystem()
{
}

Input InputSystem::state()
{
    Input out = _state;

    for(I32 key : out._keyboard._keys)
    {
        if(!_lastState.keyboard().isKeyDown(key))
        {
            out._keyboard._keysOnce.insert(key);
        }
    }

    for(I32 button : out._mouse._buttons)
    {
        if(!_lastState.mouse().isButtonDown(button))
        {
            out._mouse._buttonsOnce.insert(button);
        }
    }

    out._mouse._delta = out._mouse._position - _lastState._mouse._position;

    for(size_t i = 0; i < out._gamepads.size(); i++)
    {
        for(I32 button : out._gamepads[i]._buttons)
        {
            if(!_lastState._gamepads[i].isButtonDown(button))
            {
                out._gamepads[i]._buttonsOnce.insert(button);
            }
        }
    }

    _lastState = _state;

    return out;
}

bool InputSystem::eventFilter(QObject*, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if(!keyEvent->isAutoRepeat())
        {
            I32 key = keyEvent->key();

            _state._keyboard._keys.insert(key);
        }
    }
    else if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if(!keyEvent->isAutoRepeat())
        {
            I32 key = keyEvent->key();

            _state._keyboard._keys.erase(key);
        }
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        I32 button = mouseEvent->button();
        _state._mouse._buttons.insert(button);
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        I32 button = mouseEvent->button();
        _state._mouse._buttons.erase(button);
    }
    else if(event->type() == QEvent::MouseMove)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        I32 x = mouseEvent->x();
        I32 y = mouseEvent->y();

        _state._mouse._position = glm::vec2(x, y);
    }

    return false;
}

void InputSystem::hookup(QGamepad* gamepad)
{
    connect(gamepad, &QGamepad::axisLeftXChanged,    this, &InputSystem::axisLeftXChanged);
    connect(gamepad, &QGamepad::axisLeftYChanged,    this, &InputSystem::axisLeftYChanged);
    connect(gamepad, &QGamepad::axisRightXChanged,   this, &InputSystem::axisRightXChanged);
    connect(gamepad, &QGamepad::axisRightYChanged,   this, &InputSystem::axisRightYChanged);
    connect(gamepad, &QGamepad::buttonAChanged,      this, &InputSystem::buttonAChanged);
    connect(gamepad, &QGamepad::buttonBChanged,      this, &InputSystem::buttonBChanged);
    connect(gamepad, &QGamepad::buttonXChanged,      this, &InputSystem::buttonXChanged);
    connect(gamepad, &QGamepad::buttonYChanged,      this, &InputSystem::buttonYChanged);
    connect(gamepad, &QGamepad::buttonL1Changed,     this, &InputSystem::buttonL1Changed);
    connect(gamepad, &QGamepad::buttonR1Changed,     this, &InputSystem::buttonR1Changed);
    connect(gamepad, &QGamepad::buttonL2Changed,     this, &InputSystem::buttonL2Changed);
    connect(gamepad, &QGamepad::buttonR2Changed,     this, &InputSystem::buttonR2Changed);
    connect(gamepad, &QGamepad::buttonSelectChanged, this, &InputSystem::buttonSelectChanged);
    connect(gamepad, &QGamepad::buttonStartChanged,  this, &InputSystem::buttonStartChanged);
    connect(gamepad, &QGamepad::buttonL3Changed,     this, &InputSystem::buttonL3Changed);
    connect(gamepad, &QGamepad::buttonR3Changed,     this, &InputSystem::buttonR3Changed);
    connect(gamepad, &QGamepad::buttonUpChanged,     this, &InputSystem::buttonUpChanged);
    connect(gamepad, &QGamepad::buttonDownChanged,   this, &InputSystem::buttonDownChanged);
    connect(gamepad, &QGamepad::buttonLeftChanged,   this, &InputSystem::buttonLeftChanged);
    connect(gamepad, &QGamepad::buttonRightChanged,  this, &InputSystem::buttonRightChanged);
    connect(gamepad, &QGamepad::buttonCenterChanged, this, &InputSystem::buttonCenterChanged);
    connect(gamepad, &QGamepad::buttonGuideChanged,  this, &InputSystem::buttonGuideChanged);
}

void InputSystem::axisLeftXChanged(double value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        _state._gamepads[gamepad->deviceId()]._axisMap[QGamepadManager::AxisLeftX] = value;
    }
}

void InputSystem::axisLeftYChanged(double value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        _state._gamepads[gamepad->deviceId()]._axisMap[QGamepadManager::AxisLeftY] = value;
    }
}

void InputSystem::axisRightXChanged(double value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        _state._gamepads[gamepad->deviceId()]._axisMap[QGamepadManager::AxisRightX] = value;
    }
}

void InputSystem::axisRightYChanged(double value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        _state._gamepads[gamepad->deviceId()]._axisMap[QGamepadManager::AxisRightY] = value;
    }
}

void InputSystem::buttonAChanged(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonA);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonA);
        }
    }
}

void InputSystem::buttonBChanged(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonB);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonB);
        }
    }
}

void InputSystem::buttonXChanged(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonX);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonX);
        }
    }
}

void InputSystem::buttonYChanged(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonY);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonY);
        }
    }
}

void InputSystem::buttonL1Changed(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonL1);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonL1);
        }
    }
}

void InputSystem::buttonR1Changed(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonR1);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonR1);
        }
    }
}

void InputSystem::buttonL2Changed(double value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        _state._gamepads[gamepad->deviceId()]._axisMap[QGamepadManager::ButtonL2] = value;
    }
}

void InputSystem::buttonR2Changed(double value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        _state._gamepads[gamepad->deviceId()]._axisMap[QGamepadManager::ButtonR2] = value;
    }
}

void InputSystem::buttonSelectChanged(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonSelect);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonSelect);
        }
    }
}

void InputSystem::buttonStartChanged(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonStart);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonStart);
        }
    }
}

void InputSystem::buttonL3Changed(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonL3);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonL3);
        }
    }
}

void InputSystem::buttonR3Changed(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonR3);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonR3);
        }
    }
}

void InputSystem::buttonUpChanged(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonUp);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonUp);
        }
    }
}

void InputSystem::buttonDownChanged(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonDown);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonDown);
        }
    }
}

void InputSystem::buttonLeftChanged(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonLeft);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonLeft);
        }
    }
}

void InputSystem::buttonRightChanged(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonRight);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonRight);
        }
    }
}

void InputSystem::buttonCenterChanged(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonCenter);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonCenter);
        }
    }
}

void InputSystem::buttonGuideChanged(bool value)
{
    if(QGamepad* gamepad = dynamic_cast<QGamepad*>(sender()))
    {
        _state.gamepad(gamepad->deviceId());
        if(value)
        {
            _state._gamepads[gamepad->deviceId()]._buttons.insert(QGamepadManager::ButtonGuide);
        }
        else
        {
            _state._gamepads[gamepad->deviceId()]._buttons.erase(QGamepadManager::ButtonGuide);
        }
    }
}
