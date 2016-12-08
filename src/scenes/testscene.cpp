#include "testscene.h"

#include "components/transform.h"
#include "components/rigidbody.h"
#include "components/sprite.h"
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
    _assets->load<SpriteSheet>("images/characters_spritesheet.json");

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        e->addComponent<Transform>();
        e->addComponent<Transform>();
        e->addComponent<Transform>();
        auto rigidbody = e->addComponent<RigidBody>();

        Scene::add(e);
    }

    auto characters = _assets->get<SpriteSheet>("images/characters_spritesheet.json");

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(0, 0));

        e->addComponent<RigidBody>();

        auto sprite = e->addComponent<Sprite>();

        sprite->setSpriteSheet(characters);
        sprite->setCurrentFrame("enemy/walk_right_0");

        sprite->setSize(glm::vec2(100, 100));

        Scene::add(e);
    }

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(150, 0));

        e->addComponent<RigidBody>();

        auto sprite = e->addComponent<Sprite>();

        sprite->setSpriteSheet(characters);
        sprite->setCurrentFrame("enemy/walk_right_1");

        sprite->setSize(glm::vec2(100, 100));

        Scene::add(e);
    }

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(300, 0));

        e->addComponent<RigidBody>();

        auto sprite = e->addComponent<Sprite>();

        sprite->setSpriteSheet(characters);
        sprite->setCurrentFrame("player/walk_right_1");

        sprite->setSize(glm::vec2(100, 100));

        Scene::add(e);
    }
}

void TestScene::onExit()
{
    Scene::removeAll();
}
