#include "subsystems/scriptsystem.h"

#include <memory>

#include "assets/entity.h"
#include "components/script.h"

ScriptSystem::ScriptSystem()
{

}

ScriptSystem::~ScriptSystem()
{

}

void ScriptSystem::update(GameTime time, const std::vector<EntityHandle>& entities)
{
    for(EntityHandle entity : entities)
    {
        _update(time, entity);
    }
}

void ScriptSystem::_update(GameTime time, EntityHandle entity)
{
    std::vector<std::shared_ptr<Script> > scripts = entity->getComponents<Script>();

    for(std::shared_ptr<Script> script : scripts)
    {
        _updateScript(time, script);
    }
}

void ScriptSystem::_updateScript(GameTime time, std::shared_ptr<Script> script)
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
        script->onUpdate(time);
        break;
    }
}
