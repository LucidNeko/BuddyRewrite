#include "inputstate.h"

bool InputState::isKeyDown(I32 key) const
{
    return _keys.find(key) != _keys.end();
}

bool InputState::isKeyDownOnce(I32 key) const
{
    return _keysOnce.find(key) != _keysOnce.end();
}

bool InputState::isMouseButtonDown(I32 button) const
{
    return _mouseButtons.find(button) != _mouseButtons.end();
}

bool InputState::isMouseButtonDownOnce(I32 button) const
{
    return _mouseButtonsOnce.find(button) != _mouseButtonsOnce.end();
}

glm::vec2 InputState::mousePosition() const
{
    return _mousePosition;
}

glm::vec2 InputState::mouseDelta() const
{
    return _mousePosition - _lastMousePosition;
}
