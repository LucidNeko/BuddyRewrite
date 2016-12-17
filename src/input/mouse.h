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
        // Same as Qt values
        NoButton         = 0x00000000,
        Left       = 0x00000001,
        Right      = 0x00000002,
        Middle     = 0x00000004,
        Back       = 0x00000008,
        XButton1         = Back,
        ExtraButton1     = XButton1,
        Forward    = 0x00000010,
        XButton2         = Forward,
        ExtraButton2     = Forward,
        TaskButton       = 0x00000020,
        ExtraButton3     = TaskButton,
        ExtraButton4     = 0x00000040,
        ExtraButton5     = 0x00000080,
        ExtraButton6     = 0x00000100,
        ExtraButton7     = 0x00000200,
        ExtraButton8     = 0x00000400,
        ExtraButton9     = 0x00000800,
        ExtraButton10    = 0x00001000,
        ExtraButton11    = 0x00002000,
        ExtraButton12    = 0x00004000,
        ExtraButton13    = 0x00008000,
        ExtraButton14    = 0x00010000,
        ExtraButton15    = 0x00020000,
        ExtraButton16    = 0x00040000,
        ExtraButton17    = 0x00080000,
        ExtraButton18    = 0x00100000,
        ExtraButton19    = 0x00200000,
        ExtraButton20    = 0x00400000,
        ExtraButton21    = 0x00800000,
        ExtraButton22    = 0x01000000,
        ExtraButton23    = 0x02000000,
        ExtraButton24    = 0x04000000
    };

    static Button buttonFromQtMouseButton(I32 button);

public:
    Mouse();
    Mouse(glm::vec2 position,
          std::unordered_set<Button> buttons,
          Mouse previous = Mouse());
    Mouse(const Mouse& source);

    bool isButtonDown(Button button) const;
    bool isButtonDownOnce(Button button) const;

    glm::vec2 position() const;
    glm::vec2 delta() const;

private:
    glm::vec2 _position;
    glm::vec2 _delta;

    std::unordered_set<Button> _buttons;
    std::unordered_set<Button> _buttonsOnce;
};

class MouseWatcher
{
public:
    virtual ~MouseWatcher() {}
    virtual Mouse state() const = 0;
};

#endif // MOUSE_H
