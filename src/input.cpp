#include "input.h"

#include <QKeyEvent>

#include "logging.h"

bool Input::isKeyDown(I32 key) const
{
    return _pressedKeys.find(key) != _pressedKeys.end();
}

bool Input::isKeyDownOnce(I32 key) const
{
    return _pressedKeysOnce.find(key) != _pressedKeysOnce.end();
}

void Input::update()
{
    _pressedKeysOnce.clear();
}

bool Input::eventFilter(QObject*, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if(!keyEvent->isAutoRepeat())
        {
            I32 key = keyEvent->key();

            _pressedKeys.insert(key);
            _pressedKeysOnce.insert(key);

            LOG_INFO("Press: %d", key);
        }
    }

    if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if(!keyEvent->isAutoRepeat())
        {
            I32 key = keyEvent->key();

            _pressedKeys.erase(key);
            _pressedKeysOnce.erase(key);

            LOG_INFO("Release: %d", key);
        }
    }

    return false;
}
