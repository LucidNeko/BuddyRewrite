#include "input/mouse_watcher.h"

#include <QApplication>
#include <QMouseEvent>

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
