#ifndef SCRIPT_H
#define SCRIPT_H

#include "assets/component.h"

class Script : public Component
{
public:
    Script(EntityHandle entity = nullptr);
    ~Script();

    std::type_index type() const;

    virtual void onUpdate() = 0;
};

#endif // SCRIPT_H
