#include "inputsystem.h"

#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>

#include "logging.h"

InputSystem::InputSystem()
    : QObject(nullptr)
{
}

InputSystem::~InputSystem()
{
}

InputState InputSystem::state()
{
    InputState out = _state;

    for(I32 key : out._keys)
    {
        if(!_lastState.isKeyDown(key))
        {
            out._keysOnce.insert(key);
        }
    }

    for(I32 button : out._mouseButtons)
    {
        if(!_lastState.isMouseButtonDown(button))
        {
            out._mouseButtonsOnce.insert(button);
        }
    }

    out._mouseDelta = out._mousePosition - _lastState._mousePosition;

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

            _state._keys.insert(key);
        }
    }
    else if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if(!keyEvent->isAutoRepeat())
        {
            I32 key = keyEvent->key();

            _state._keys.erase(key);
        }
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        I32 button = mouseEvent->button();
        _state._mouseButtons.insert(button);
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        I32 button = mouseEvent->button();
        _state._mouseButtons.erase(button);
    }
    else if(event->type() == QEvent::MouseMove)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        I32 x = mouseEvent->x();
        I32 y = mouseEvent->y();

        _state._mousePosition = glm::vec2(x, y);
    }

    return false;
}
