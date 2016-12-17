#ifndef GAMEPAD_WATCHER_H
#define GAMEPAD_WATCHER_H

#include <unordered_map>
#include <unordered_set>

#include <QObject>

#include "input/gamepad.h"
#include "types.h"

class GamepadWatcherImpl : public QObject, public GamepadWatcher
{
    Q_OBJECT

public:
    GamepadWatcherImpl(I32 controllerIndex, QObject* parent = nullptr);

    Gamepad state() const override;

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
    I32 _deviceId;
    std::unordered_set<Gamepad::Button> _buttons;
    std::unordered_map<Gamepad::Axis, F32> _axisMap;
    mutable Gamepad _lastState;
};

#endif // GAMEPAD_WATCHER_H
