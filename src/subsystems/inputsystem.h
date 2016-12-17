#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <memory>
#include <vector>

#include <QObject>

#include "input/input.h"
#include "types.h"

#include "input/gamepad.h"
#include "input/keyboard.h"
#include "input/mouse.h"

class MouseWatcherImpl : public QObject, public MouseWatcher
{
    Q_OBJECT

public:
    MouseWatcherImpl(QObject* parent = nullptr);

    Mouse state() const override;

    bool eventFilter(QObject*, class QEvent* event);

private:
    glm::vec2 _position;
    std::unordered_set<I32> _buttons;
    mutable Mouse _lastState;
};

class KeyboardWatcherImpl : public QObject, public KeyboardWatcher
{
    Q_OBJECT

public:
    KeyboardWatcherImpl(QObject* parent = nullptr);

    Keyboard state() const override;

    bool eventFilter(QObject*, class QEvent* event);

private:
    std::unordered_set<I32> _keys;
    mutable Keyboard _lastState;
};

class GamepadWatcherImpl : public QObject, public GamepadWatcher
{
    Q_OBJECT

public:
    GamepadWatcherImpl(I32 controllerIndex, QObject* parent = nullptr);

    Gamepad state() const override;

private slots:
    void axisLeftXChanged(double value);
    void axisLeftYChanged(double value);
    void axisRightXChanged(double value);
    void axisRightYChanged(double value);
    void buttonAChanged(bool value);
    void buttonBChanged(bool value);
    void buttonXChanged(bool value);
    void buttonYChanged(bool value);
    void buttonL1Changed(bool value);
    void buttonR1Changed(bool value);
    void buttonL2Changed(double value);
    void buttonR2Changed(double value);
    void buttonSelectChanged(bool value);
    void buttonStartChanged(bool value);
    void buttonL3Changed(bool value);
    void buttonR3Changed(bool value);
    void buttonUpChanged(bool value);
    void buttonDownChanged(bool value);
    void buttonLeftChanged(bool value);
    void buttonRightChanged(bool value);
    void buttonCenterChanged(bool value);
    void buttonGuideChanged(bool value);

private:
    I32 _deviceId;
    std::unordered_set<I32> _buttons;
    std::unordered_map<I32, F32> _axisMap;
    mutable Gamepad _lastState;
};

class InputSystem : public QObject
{
    Q_OBJECT

public:
    InputSystem();
    ~InputSystem();

    Input state();

private:
    KeyboardWatcher* _keyboardWatcher;
    MouseWatcher* _mouseWatcher;
    GamepadWatcher* _player1Watcher;
    GamepadWatcher* _player2Watcher;
    GamepadWatcher* _player3Watcher;
    GamepadWatcher* _player4Watcher;
};

#endif // INPUTSYSTEM_H
