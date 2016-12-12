#include "script.h"

#include <unordered_map>
#include <functional>

Script::Script(EntityHandle entity)
    : Component(entity),
      _stage(Stage::START)
{
}

std::type_index Script::type() const
{
    return std::type_index(typeid(Script));
}

Script::Stage Script::stage() const
{
    return _stage;
}

void Script::setStage(Script::Stage stage)
{
    _stage = stage;
}

void Script::call(std::string method)
{
//    TODO: Maybe don't do any of this anyway?

//    static std::unordered_map<std::string, std::function<void(void)> > fns({
//       { "onStart", &Script::onStart }
//    });

//    auto it = fns.find(method);
//    if(it != fns.end())
//    {
//        it->second();
//    }

    if(method == "onStart") { return onStart(); }
}
