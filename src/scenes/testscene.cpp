#include "testscene.h"

#include "components/transform.h"
#include "components/rigidbody.h"
#include "components/sprite.h"
#include "entity.h"
#include "entityfactory.h"
#include "logging.h"
#include "resources/io/resources.h"
#include "resources/spritesheet.h"
#include "services.h"
#include "resources/texture.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::onEnter()
{
    Services::get<Resources>()->load<SpriteSheet>("player.png");
    Services::get<Resources>()->load<SpriteSheet>("enemy.png");
    Services::get<Resources>()->load<SpriteSheet>("tiles.png");

    Services::get<Resources>()->load<Texture>("debug.png");

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        e->addComponent<Transform>();
        e->addComponent<Transform>();
        e->addComponent<Transform>();
        auto rigidbody = e->addComponent<RigidBody>();

        Scene::add(e);
    }

    auto enemy = Services::get<Resources>()->get<SpriteSheet>("enemy.png");
    auto player = Services::get<Resources>()->get<SpriteSheet>("player.png");
    auto tiles = Services::get<Resources>()->get<SpriteSheet>("tiles.png");

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(0, 0));

        e->addComponent<RigidBody>();

        auto sprite = e->addComponent<Sprite>();

        sprite->setSpriteSheet(tiles);

        sprite->setSize(glm::vec2(100, 100));

        Scene::add(e);
    }

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(150, 0));

        e->addComponent<RigidBody>();

        auto sprite = e->addComponent<Sprite>();

        sprite->setSpriteSheet(player);

        sprite->setSize(glm::vec2(100, 100));

        Scene::add(e);
    }

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(300, 0));

        e->addComponent<RigidBody>();

        auto sprite = e->addComponent<Sprite>();

        sprite->setSpriteSheet(enemy);

        sprite->setSize(glm::vec2(100, 100));

        Scene::add(e);
    }
}

void TestScene::onExit()
{
    Scene::removeAll();
}
