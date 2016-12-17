#include "input/mouse.h"

Mouse::Mouse()
{
}

Mouse::Mouse(glm::vec2 position, std::unordered_set<I32> buttons, Mouse previous)
    : _position(position),
      _buttons(buttons)
{
    for(I32 button : _buttons)
    {
        if(!previous.isButtonDown(button))
        {
            _buttonsOnce.insert(button);
        }
    }

    _delta = _position - previous.position();
}

Mouse::Mouse(const Mouse& source)
    : _position(source.position()),
      _delta(source._delta),
      _buttons(source._buttons),
      _buttonsOnce(source._buttonsOnce)
{
}

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
