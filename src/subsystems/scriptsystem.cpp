#include "subsystems/scriptsystem.h"

#include <memory>

#include "assets/entity.h"
#include "components/script.h"
#include "input/input.h"

ScriptSystem::ScriptSystem()
{

}

ScriptSystem::~ScriptSystem()
{

}

void ScriptSystem::update(GameTime time, const Input& input, const std::vector<EntityHandle>& entities)
{
    for(EntityHandle entity : entities)
    {
        _update(time, input, entity);
    }
}

void ScriptSystem::_update(GameTime time, const Input& input, EntityHandle entity)
{
    std::vector<std::shared_ptr<Script> > scripts = entity->getComponents<Script>();

    for(std::shared_ptr<Script> script : scripts)
    {
        _updateScript(time, input, script);
    }
}

void ScriptSystem::_updateScript(GameTime time, const Input& input, std::shared_ptr<Script> script)
{
    switch(script->stage())
    {
    case Script::Stage::START:
//        script->onStart();
        script->call("onStart");
        script->setStage(Script::Stage::ENTER);
        break;
    case Script::Stage::ENTER:
        script->onEnter();
        script->setStage(Script::Stage::UPDATE);
        break;
    case Script::Stage::UPDATE:
        script->onUpdate(time, input);
        break;
    }
}
