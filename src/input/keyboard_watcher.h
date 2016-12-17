#ifndef KEYBOARD_WATCHER_H
#define KEYBOARD_WATCHER_H

#include <unordered_set>
#include <QObject>
#include "input/keyboard.h"

class KeyboardWatcherImpl : public QObject, public KeyboardWatcher
{
    Q_OBJECT

public:
    KeyboardWatcherImpl(QObject* parent = nullptr);
    ~KeyboardWatcherImpl();

    Keyboard state() const override;

    bool eventFilter(QObject*, class QEvent* event);

private:
    std::unordered_set<Keyboard::Key> _keys;
    mutable Keyboard _lastState;
};

#endif // KEYBOARD_WATCHER_H
