#ifndef MOUSE_H
#define MOUSE_H

#include <unordered_set>

#include <glm/vec2.hpp>

#include "types.h"

class Mouse
{
public:
    enum class Button
    {
    };

public:
    Mouse();
    Mouse(glm::vec2 position,
          std::unordered_set<I32> buttons,
          Mouse previous = Mouse());
    Mouse(const Mouse& source);

    bool isButtonDown(I32 button) const;
    bool isButtonDownOnce(I32 button) const;

    glm::vec2 position() const;
    glm::vec2 delta() const;

private:
    glm::vec2 _position;
    glm::vec2 _delta;

    std::unordered_set<I32> _buttons;
    std::unordered_set<I32> _buttonsOnce;
};

class MouseWatcher
{
public:
    virtual Mouse state() const = 0;
};

#endif // MOUSE_H
