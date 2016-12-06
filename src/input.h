#ifndef INPUT_H
#define INPUT_H

#include <unordered_set>

#include <QObject>
#include <QEvent>

#include "types.h"

class Input : public QObject
{
public:
    Input() = default;
    ~Input() = default;

    bool isKeyDown(I32 key) const;

    bool isKeyDownOnce(I32 key) const;

    void update();

public:
    bool eventFilter(QObject*, QEvent*);

private:
    std::unordered_set<I32> _pressedKeys;
    std::unordered_set<I32> _pressedKeysOnce;
};

#endif // INPUT_H
