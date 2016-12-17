#include "input/keyboard_watcher.h"

#include <QApplication>
#include <QKeyEvent>

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
