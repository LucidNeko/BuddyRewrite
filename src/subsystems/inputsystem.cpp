#include "inputsystem.h"

#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QtGamepad/QGamepad>

#include "logging.h"

InputSystem::InputSystem()
    : QObject(nullptr),
      _keyboardWatcher(nullptr),
      _mouseWatcher(nullptr),
      _player1Watcher(nullptr),
      _player2Watcher(nullptr),
      _player3Watcher(nullptr),
      _player4Watcher(nullptr)
{
    KeyboardWatcherImpl* keyboardWatcher = new KeyboardWatcherImpl(this);
    MouseWatcherImpl* mouseWatcher = new MouseWatcherImpl(this);
    GamepadWatcherImpl* player1Watcher = new GamepadWatcherImpl(0, this);
    GamepadWatcherImpl* player2Watcher = new GamepadWatcherImpl(1, this);
    GamepadWatcherImpl* player3Watcher = new GamepadWatcherImpl(2, this);
    GamepadWatcherImpl* player4Watcher = new GamepadWatcherImpl(3, this);
    this->installEventFilter(keyboardWatcher);
    this->installEventFilter(mouseWatcher);
    this->installEventFilter(player1Watcher);
    this->installEventFilter(player2Watcher);
    this->installEventFilter(player3Watcher);
    this->installEventFilter(player4Watcher);
    _keyboardWatcher = keyboardWatcher;
    _mouseWatcher = mouseWatcher;
    _player1Watcher = player1Watcher;
    _player2Watcher = player2Watcher;
    _player3Watcher = player3Watcher;
    _player4Watcher = player4Watcher;
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
        _buttons.insert(mouseEvent->button());
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        _buttons.erase(mouseEvent->button());
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
            _keys.insert(keyEvent->key());
        }
    }
    else if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if(!keyEvent->isAutoRepeat())
        {
            _keys.erase(keyEvent->key());
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
        _axisMap[QGamepadManager::AxisLeftX] = value;
    }
}

void GamepadWatcherImpl::axisLeftYChanged(double value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        _axisMap[QGamepadManager::AxisLeftY] = value;
    }
}

void GamepadWatcherImpl::axisRightXChanged(double value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        _axisMap[QGamepadManager::AxisRightX] = value;
    }
}

void GamepadWatcherImpl::axisRightYChanged(double value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        _axisMap[QGamepadManager::AxisRightY] = value;
    }
}

void GamepadWatcherImpl::buttonAChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonA);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonA);
        }
    }
}

void GamepadWatcherImpl::buttonBChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonB);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonB);
        }
    }
}

void GamepadWatcherImpl::buttonXChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonX);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonX);
        }
    }
}

void GamepadWatcherImpl::buttonYChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonY);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonY);
        }
    }
}

void GamepadWatcherImpl::buttonL1Changed(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonL1);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonL1);
        }
    }
}

void GamepadWatcherImpl::buttonR1Changed(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonR1);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonR1);
        }
    }
}

void GamepadWatcherImpl::buttonL2Changed(double value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        _axisMap[QGamepadManager::ButtonL2] = value;
    }
}

void GamepadWatcherImpl::buttonR2Changed(double value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        _axisMap[QGamepadManager::ButtonR2] = value;
    }
}

void GamepadWatcherImpl::buttonSelectChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonSelect);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonSelect);
        }
    }
}

void GamepadWatcherImpl::buttonStartChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonStart);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonStart);
        }
    }
}

void GamepadWatcherImpl::buttonL3Changed(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonL3);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonL3);
        }
    }
}

void GamepadWatcherImpl::buttonR3Changed(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonR3);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonR3);
        }
    }
}

void GamepadWatcherImpl::buttonUpChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonUp);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonUp);
        }
    }
}

void GamepadWatcherImpl::buttonDownChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonDown);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonDown);
        }
    }
}

void GamepadWatcherImpl::buttonLeftChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonLeft);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonLeft);
        }
    }
}

void GamepadWatcherImpl::buttonRightChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonRight);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonRight);
        }
    }
}

void GamepadWatcherImpl::buttonCenterChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonCenter);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonCenter);
        }
    }
}

void GamepadWatcherImpl::buttonGuideChanged(bool value)
{
    if(_deviceId == static_cast<QGamepad*>(sender())->deviceId())
    {
        if(value)
        {
            _buttons.insert(QGamepadManager::ButtonGuide);
        }
        else
        {
            _buttons.erase(QGamepadManager::ButtonGuide);
        }
    }
}
