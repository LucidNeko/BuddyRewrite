#include "input/mouse.h"

Mouse::Button Mouse::buttonFromQtMouseButton(I32 button)
{
    return static_cast<Button>(button);
}

Mouse::Mouse()
{
}

Mouse::Mouse(glm::vec2 position, std::unordered_set<Button, EnumClassHash> buttons, Mouse previous)
    : _position(position),
      _buttons(buttons)
{
    for(Button button : _buttons)
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

bool Mouse::isButtonDown(Button button) const
{
    return _buttons.find(button) != _buttons.end();
}

bool Mouse::isButtonDownOnce(Button button) const
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
