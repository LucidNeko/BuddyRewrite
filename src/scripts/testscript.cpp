#include "scripts/testscript.h"

#include <cmath>
#include <memory>

#include "assets/entity.h"
#include "components/rigidbody.h"
#include "components/transform.h"
#include "logging.h"

TestScript::TestScript(EntityHandle entity)
    : Script(entity),
      _first(true),
      _elapsed(0)
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

    _elapsed += time.seconds();

    F32 amt = std::sin(_elapsed) * 100;

    if(auto transform = entity()->getComponent<Transform>())
    {
        glm::vec2 pos = transform->position();
        pos.y -= amt * time.seconds();
        transform->setPosition(pos);
    }

//    if(auto rb = entity()->getComponent<RigidBody>())
//    {
//        if(input.isKeyDownOnce(Qt::Key_Space))
//        {
//            rb->setVelocity(glm::vec2(0, -900));
//        }
//    }


}

void TestScript::onExit()
{
    LOG_INFO("TestScript::onExit");
}
