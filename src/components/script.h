#ifndef SCRIPT_H
#define SCRIPT_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

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

    template<typename T>
    static std::shared_ptr<T> create(std::string type)
    {
        return std::dynamic_pointer_cast<T>(create(type));
    }
    static std::shared_ptr<Script> create(std::string type);

public:
    Script(EntityHandle entity = nullptr);
    virtual ~Script() {}

    std::type_index type() const;

    Script::Stage stage() const;
    void setStage(Script::Stage stage);

    void call(std::string method);

    virtual void onStart() {}
    virtual void onEnter() {}
    virtual void onUpdate(GameTime, const class Input&) {}
    virtual void onExit() {}

private:
    Stage _stage;
};

#endif // SCRIPT_H
