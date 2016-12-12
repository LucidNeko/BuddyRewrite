#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>

#include "assets/component.h"
#include "gametime.h"

class Script : public Component
{
public:
    enum class Stage
    {
        START,
        ENTER,
        UPDATE
    };

public:
    Script(EntityHandle entity = nullptr);
    virtual ~Script() {}

    std::type_index type() const;

    Script::Stage stage() const;
    void setStage(Script::Stage stage);

    void call(std::string method);

    virtual void onStart() {}
    virtual void onEnter() {}
    virtual void onUpdate(GameTime) {}
    virtual void onExit() {}

private:
    Stage _stage;
};

#endif // SCRIPT_H
