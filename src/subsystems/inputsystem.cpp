#include "inputsystem.h"

#include <QApplication>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QtGamepad/QGamepad>

#include "logging.h"

InputSystem::InputSystem()
    : _keyboardWatcher(new KeyboardWatcherImpl()),
      _mouseWatcher(new MouseWatcherImpl()),
      _player1Watcher(new GamepadWatcherImpl(0)),
      _player2Watcher(new GamepadWatcherImpl(1)),
      _player3Watcher(new GamepadWatcherImpl(2)),
      _player4Watcher(new GamepadWatcherImpl(3))
{
}

InputSystem::~InputSystem()
{
}

Input InputSystem::state()
{
    Keyboard keyboard = _keyboardWatcher->state();
    Mouse mouse = _mouseWatcher->state();
    std::vector<Gamepad> gamepads = {
        _player1Watcher->state(),
        _player2Watcher->state(),
        _player3Watcher->state(),
        _player4Watcher->state(),
    };

    return Input(keyboard, mouse, gamepads);
}

MouseWatcherImpl::MouseWatcherImpl(QObject* parent)
    : QObject(parent)
{
    qApp->installEventFilter(this);
}

MouseWatcherImpl::~MouseWatcherImpl()
{
    qApp->removeEventFilter(this);
}

Mouse MouseWatcherImpl::state() const
{
    Mouse state(_position, _buttons, _lastState);
    _lastState = state;
    return state;
}

bool MouseWatcherImpl::eventFilter(QObject*, QEvent* event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        _buttons.insert(Mouse::buttonFromQtMouseButton(mouseEvent->button()));
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        _buttons.erase(Mouse::buttonFromQtMouseButton(mouseEvent->button()));
    }
    else if(event->type() == QEvent::MouseMove)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        _position = glm::vec2(mouseEvent->x(), mouseEvent->y());
    }

    return false;
}

KeyboardWatcherImpl::KeyboardWatcherImpl(QObject* parent)
    : QObject(parent)
{
    qApp->installEventFilter(this);
}

KeyboardWatcherImpl::~KeyboardWatcherImpl()
{
    qApp->removeEventFilter(this);
}

Keyboard KeyboardWatcherImpl::state() const
{
    Keyboard state(_keys, _lastState);
    _lastState = state;
    return state;
}

bool KeyboardWatcherImpl::eventFilter(QObject*, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if(!keyEvent->isAutoRepeat())
        {
            _keys.insert(Keyboard::keyFromQtKey(keyEvent->key()));
        }
    }
    else if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if(!keyEvent->isAutoRepeat())
        {
            _keys.erase(Keyboard::keyFromQtKey(keyEvent->key()));
        }
    }

    return false;
}

GamepadWatcherImpl::GamepadWatcherImpl(I32 controllerIndex, QObject* parent)
    : QObject(parent),
      _deviceId(0)
{
    //TODO: Does the destructor get called because of parent connections?
    QGamepad* qtGamepad = new QGamepad(controllerIndex, this);
    _deviceId = qtGamepad->deviceId(); //TODO: Listen for deviceIdChanged?

    connect(qtGamepad, &QGamepad::axisLeftXChanged,    this, &GamepadWatcherImpl::axisLeftXChanged);
    connect(qtGamepad, &QGamepad::axisLeftYChanged,    this, &GamepadWatcherImpl::axisLeftYChanged);
    connect(qtGamepad, &QGamepad::axisRightXChanged,   this, &GamepadWatcherImpl::axisRightXChanged);
    connect(qtGamepad, &QGamepad::axisRightYChanged,   this, &GamepadWatcherImpl::axisRightYChanged);
    connect(qtGamepad, &QGamepad::buttonAChanged,      this, &GamepadWatcherImpl::buttonAChanged);
    connect(qtGamepad, &QGamepad::buttonBChanged,      this, &GamepadWatcherImpl::buttonBChanged);
    connect(qtGamepad, &QGamepad::buttonXChanged,      this, &GamepadWatcherImpl::buttonXChanged);
    connect(qtGamepad, &QGamepad::buttonYChanged,      this, &GamepadWatcherImpl::buttonYChanged);
    connect(qtGamepad, &QGamepad::buttonL1Changed,     this, &GamepadWatcherImpl::buttonL1Changed);
    connect(qtGamepad, &QGamepad::buttonR1Changed,     this, &GamepadWatcherImpl::buttonR1Changed);
    connect(qtGamepad, &QGamepad::buttonL2Changed,     this, &GamepadWatcherImpl::buttonL2Changed);
    connect(qtGamepad, &QGamepad::buttonR2Changed,     this, &GamepadWatcherImpl::buttonR2Changed);
    connect(qtGamepad, &QGamepad::buttonSelectChanged, this, &GamepadWatcherImpl::buttonSelectChanged);
    connect(qtGamepad, &QGamepad::buttonStartChanged,  this, &GamepadWatcherImpl::buttonStartChanged);
    connect(qtGamepad, &QGamepad::buttonL3Changed,     this, &GamepadWatcherImpl::buttonL3Changed);
    connect(qtGamepad, &QGamepad::buttonR3Changed,     this, &GamepadWatcherImpl::buttonR3Changed);
    connect(qtGamepad, &QGamepad::buttonUpChanged,     this, &GamepadWatcherImpl::buttonUpChanged);
    connect(qtGamepad, &QGamepad::buttonDownChanged,   this, &GamepadWatcherImpl::buttonDownChanged);
    connect(qtGamepad, &QGamepad::buttonLeftChanged,   this, &GamepadWatcherImpl::buttonLeftChanged);
    connect(qtGamepad, &QGamepad::buttonRightChanged,  this, &GamepadWatcherImpl::buttonRightChanged);
    connect(qtGamepad, &QGamepad::buttonCenterChanged, this, &GamepadWatcherImpl::buttonCenterChanged);
    connect(qtGamepad, &QGamepad::buttonGuideChanged,  this, &GamepadWatcherImpl::buttonGuideChanged);
}

Gamepad GamepadWatcherImpl::state() const
{
    Gamepad state(_buttons, _axisMap, _lastState);
    _lastState = state;
    return state;
}

void GamepadWatcherImpl::axisLeftXChanged(double value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        _axisMap[Gamepad::Axis::LeftX] = value;
    }
}

void GamepadWatcherImpl::axisLeftYChanged(double value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        _axisMap[Gamepad::Axis::LeftY] = value;
    }
}

void GamepadWatcherImpl::axisRightXChanged(double value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        _axisMap[Gamepad::Axis::RightX] = value;
    }
}

void GamepadWatcherImpl::axisRightYChanged(double value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        _axisMap[Gamepad::Axis::RightY] = value;
    }
}

void GamepadWatcherImpl::buttonAChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::A);
        }
        else
        {
            _buttons.erase(Gamepad::Button::A);
        }
    }
}

void GamepadWatcherImpl::buttonBChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::B);
        }
        else
        {
            _buttons.erase(Gamepad::Button::B);
        }
    }
}

void GamepadWatcherImpl::buttonXChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::X);
        }
        else
        {
            _buttons.erase(Gamepad::Button::X);
        }
    }
}

void GamepadWatcherImpl::buttonYChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::Y);
        }
        else
        {
            _buttons.erase(Gamepad::Button::Y);
        }
    }
}

void GamepadWatcherImpl::buttonL1Changed(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::L1);
        }
        else
        {
            _buttons.erase(Gamepad::Button::L1);
        }
    }
}

void GamepadWatcherImpl::buttonR1Changed(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::R1);
        }
        else
        {
            _buttons.erase(Gamepad::Button::R1);
        }
    }
}

void GamepadWatcherImpl::buttonL2Changed(double value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        _axisMap[Gamepad::Axis::L2] = value;
    }
}

void GamepadWatcherImpl::buttonR2Changed(double value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        _axisMap[Gamepad::Axis::R2] = value;
    }
}

void GamepadWatcherImpl::buttonSelectChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::Select);
        }
        else
        {
            _buttons.erase(Gamepad::Button::Select);
        }
    }
}

void GamepadWatcherImpl::buttonStartChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::Start);
        }
        else
        {
            _buttons.erase(Gamepad::Button::Start);
        }
    }
}

void GamepadWatcherImpl::buttonL3Changed(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::L3);
        }
        else
        {
            _buttons.erase(Gamepad::Button::L3);
        }
    }
}

void GamepadWatcherImpl::buttonR3Changed(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::R3);
        }
        else
        {
            _buttons.erase(Gamepad::Button::R3);
        }
    }
}

void GamepadWatcherImpl::buttonUpChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::Up);
        }
        else
        {
            _buttons.erase(Gamepad::Button::Up);
        }
    }
}

void GamepadWatcherImpl::buttonDownChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::Down);
        }
        else
        {
            _buttons.erase(Gamepad::Button::Down);
        }
    }
}

void GamepadWatcherImpl::buttonLeftChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::Left);
        }
        else
        {
            _buttons.erase(Gamepad::Button::Left);
        }
    }
}

void GamepadWatcherImpl::buttonRightChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::Right);
        }
        else
        {
            _buttons.erase(Gamepad::Button::Right);
        }
    }
}

void GamepadWatcherImpl::buttonCenterChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::Center);
        }
        else
        {
            _buttons.erase(Gamepad::Button::Center);
        }
    }
}

void GamepadWatcherImpl::buttonGuideChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(Gamepad::Button::Guide);
        }
        else
        {
            _buttons.erase(Gamepad::Button::Guide);
        }
    }
}
