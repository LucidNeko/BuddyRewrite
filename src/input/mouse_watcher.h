#ifndef MOUSE_WATCHER_H
#define MOUSE_WATCHER_H

#include <unordered_set>
#include <QObject>
#include <glm/vec2.hpp>
#include "enumclasshash.h"
#include "input/mouse.h"

class MouseWatcherImpl : public QObject, public MouseWatcher
{
    Q_OBJECT

public:
    MouseWatcherImpl(QObject* parent = nullptr);
    ~MouseWatcherImpl();

    Mouse state() const override;

    bool eventFilter(QObject*, class QEvent* event);

private:
    glm::vec2 _position;
    std::unordered_set<Mouse::Button, EnumClassHash> _buttons;
    mutable Mouse _lastState;
};

#endif // MOUSE_WATCHER_H
