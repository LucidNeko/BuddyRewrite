#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <QObject>

#include "inputstate.h"
#include "types.h"

class InputSystem : public QObject
{
public:
    InputSystem();
    ~InputSystem();

    InputState state();

public:
    bool eventFilter(QObject*, class QEvent* event);

private:
    InputState _lastState;
    InputState _state;
};

#endif // INPUTSYSTEM_H
