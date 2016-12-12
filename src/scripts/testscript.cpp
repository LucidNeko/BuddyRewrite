#include "scripts/testscript.h"

#include "assets/entity.h"
#include "logging.h"

TestScript::TestScript(EntityHandle entity)
    : Script(entity),
      _first(true)
{
}

TestScript::~TestScript()
{
}

void TestScript::onStart()
{
    LOG_INFO("TestScript::onStart");
}

void TestScript::onEnter()
{
    LOG_INFO("TestScript::onEnter");
}

void TestScript::onUpdate(GameTime time)
{
    if(_first)
    {
        LOG_INFO("TestScript::onUpdate(%.5f)", time.seconds());
        _first = false;
    }

}

void TestScript::onExit()
{
    LOG_INFO("TestScript::onExit");
}
