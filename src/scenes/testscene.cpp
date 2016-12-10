#include "testscene.h"

#include "components/transform.h"
#include "components/rigidbody.h"
#include "components/sprite.h"
#include "components/animation.h"
#include "entity.h"
#include "entityfactory.h"
#include "logging.h"
#include "assets/spritesheet.h"
#include "services.h"
#include "assets/texture.h"

TestScene::TestScene(AssetsHandle assets)
    : Scene(assets)
{
}

TestScene::~TestScene()
{
}

void TestScene::onEnter()
{
    auto characters = _assets->get<SpriteSheet>("images/characters");
    auto tiles = _assets->get<SpriteSheet>("images/tiles");

    // Will get freed because no references
    _assets->load<Texture>("images/debug");

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        e->addComponent<Transform>();
        e->addComponent<Transform>();
        e->addComponent<Transform>();
        auto rigidbody = e->addComponent<RigidBody>();

        Scene::add(e);
    }

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(128, 0));

        e->addComponent<RigidBody>();

        auto sprite = e->addComponent<Sprite>();

        sprite->setSpriteSheet(characters);

        sprite->setSize(glm::vec2(128, 128));

        auto anim = e->addComponent<Animation>();

        SpriteSheetSequence sequence;
        if(characters->sequence("enemy_walk_right", sequence))
        {
            anim->setSequence(sequence);
        }

        Scene::add(e);
    }

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(128*2, 0));

        e->addComponent<RigidBody>();

        auto sprite = e->addComponent<Sprite>();

        sprite->setSpriteSheet(tiles);

        SpriteSheetFrame frame;
        if(tiles->frame("tiles/0000", frame))
        {
            sprite->setCurrentFrame(frame);
        }

        sprite->setSize(glm::vec2(128, 128));

        Scene::add(e);
    }
    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(128*3, 0));

        e->addComponent<RigidBody>();

        auto sprite = e->addComponent<Sprite>();

        sprite->setSpriteSheet(tiles);

        SpriteSheetFrame frame;
        if(tiles->frame("tiles/0001", frame))
        {
            sprite->setCurrentFrame(frame);
        }

        sprite->setSize(glm::vec2(128, 128));

        Scene::add(e);
    }

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(128*4, 0));

        e->addComponent<RigidBody>();

        auto sprite = e->addComponent<Sprite>();

        sprite->setSpriteSheet(characters);

        auto anim = e->addComponent<Animation>();

        SpriteSheetSequence sequence;
        if(characters->sequence("player_walk_left", sequence))
        {
            anim->setSequence(sequence);
        }

        sprite->setSize(glm::vec2(128, 128));

        Scene::add(e);
    }
}

void TestScene::onExit()
{
    Scene::removeAll();
}
