#include "inputsystem.h"

#include "input/gamepad_watcher.h"
#include "input/keyboard_watcher.h"
#include "input/mouse_watcher.h"

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
