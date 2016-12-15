#include "input/mouse.h"


bool Mouse::isButtonDown(I32 button) const
{
    return _buttons.find(button) != _buttons.end();
}

bool Mouse::isButtonDownOnce(I32 button) const
{
    return _buttonsOnce.find(button) != _buttonsOnce.end();
}

glm::vec2 Mouse::position() const
{
    return _position;
}

glm::vec2 Mouse::delta() const
{
    return _delta;
}
