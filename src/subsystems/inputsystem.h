#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <memory>

#include "input/input.h"

class InputSystem
{
public:
    InputSystem();
    ~InputSystem();

    Input state();

private:
    std::unique_ptr<class KeyboardWatcher> _keyboardWatcher;
    std::unique_ptr<class MouseWatcher> _mouseWatcher;
    std::unique_ptr<class GamepadWatcher> _player1Watcher;
    std::unique_ptr<class GamepadWatcher> _player2Watcher;
    std::unique_ptr<class GamepadWatcher> _player3Watcher;
    std::unique_ptr<class GamepadWatcher> _player4Watcher;
};

#endif // INPUTSYSTEM_H
