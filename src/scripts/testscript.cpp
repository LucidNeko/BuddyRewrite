#include "scripts/testscript.h"

#include <cmath>
#include <memory>

#include <Qt>
#include <QGamepad>

#include "assets/entity.h"
#include "components/rigidbody.h"
#include "components/transform.h"
#include "components/sprite.h"
#include "components/animation.h"
#include "input/input.h"
#include "logging.h"

TestScript::TestScript(EntityHandle entity)
    : Script(entity),
      _first(true),
      _elapsed(0),
      _dir(-1)
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

void TestScript::onUpdate(GameTime time, const Input& input)
{
    if(_first)
    {
        LOG_INFO("TestScript::onUpdate(%.5f)", time.seconds());
        _first = false;
    }

    _elapsed += time.seconds();

    if(auto rb = entity()->getComponent<RigidBody>())
    {
//        if(input.keyboard().isKeyDownOnce(Qt::Key_Space))
//        {
//            rb->setVelocity(glm::vec2(0, -900));
//        }
        const Gamepad& gp = input.gamepad(0);

        glm::vec2 velocity = rb->velocity();
        glm::vec2 leftStick = glm::vec2(gp.getAxis(Gamepad::Axis::LeftX), gp.getAxis(Gamepad::Axis::LeftY));

        if(gp.isButtonDownOnce(Gamepad::Button::A))
        {
            velocity.y = -750;
        }
        velocity.x = leftStick.x * 300;

        rb->setVelocity(velocity);


        auto sprite = entity()->getComponent<Sprite>();
        auto animation = entity()->getComponent<Animation>();
        if(sprite && animation && std::abs(rb->velocity().x) > 0.2)
        {
            I32 newDir = rb->velocity().x > 0 ? 1 : -1;

            if(newDir != _dir)
            {
                _dir = newDir;

                SpriteSheetSequence sequence;
                if(_dir == 1)
                {
                    if(sprite->spriteSheet()->sequence("player_walk_right", sequence))
                    {
                        animation->setSequence(sequence);
                    }
                }
                else
                {
                    if(sprite->spriteSheet()->sequence("player_walk_left", sequence))
                    {
                        animation->setSequence(sequence);
                    }
                }
            }


        }
    }



}

void TestScript::onExit()
{
    LOG_INFO("TestScript::onExit");
}
