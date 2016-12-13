#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <unordered_set>

#include <glm/vec2.hpp>

#include "types.h"

class InputState
{
public:
    bool isKeyDown(I32 key) const;
    bool isKeyDownOnce(I32 key) const;

    bool isMouseButtonDown(I32 button) const;
    bool isMouseButtonDownOnce(I32 button) const;

    glm::vec2 mousePosition() const;
    glm::vec2 mouseDelta() const;

private:
    std::unordered_set<I32> _keys;
    mutable std::unordered_set<I32> _keysOnce;

    glm::vec2 _mousePosition;
    glm::vec2 _mouseDelta;

    std::unordered_set<I32> _mouseButtons;
    mutable std::unordered_set<I32> _mouseButtonsOnce;

    friend class InputSystem;
};

#endif // INPUTSTATE_H
