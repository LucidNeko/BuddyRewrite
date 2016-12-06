#ifndef SCRIPT_H
#define SCRIPT_H

#include "components/component.h"

class Script : public Component
{
public:
    Script(EntityHandle entity = nullptr);
    ~Script();

    Component::Type type() const;

    virtual void onUpdate() = 0;
};

#endif // SCRIPT_H
