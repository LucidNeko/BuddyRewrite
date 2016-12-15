#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <memory>
#include <vector>

#include <QObject>

#include "input/input.h"
#include "types.h"

class InputSystem : public QObject
{
    Q_OBJECT

public:
    InputSystem();
    ~InputSystem();

    Input state();

public:
    bool eventFilter(QObject*, class QEvent* event);

private:
    void hookup(class QGamepad* gamepad);

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
    Input _lastState;
    Input _state;

    std::vector<std::shared_ptr<class QGamepad> > _gamepads;
};

#endif // INPUTSYSTEM_H
