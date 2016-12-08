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
    _assets->load<SpriteSheet>("images/characters/spritesheet.json");
    _assets->load<SpriteSheet>("images/tiles/spritesheet.json");

    // Will get freed because no references
    _assets->load<Texture>("images/debug/texture.json");

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        e->addComponent<Transform>();
        e->addComponent<Transform>();
        e->addComponent<Transform>();
        auto rigidbody = e->addComponent<RigidBody>();

        Scene::add(e);
    }

    auto characters = _assets->get<SpriteSheet>("images/characters/spritesheet.json");
    auto tiles = _assets->get<SpriteSheet>("images/tiles/spritesheet.json");

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(50, 0));

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

        sprite->setSpriteSheet(tiles);
        sprite->setCurrentFrame("tiles/0000");

        sprite->setSize(glm::vec2(100, 100));

        Scene::add(e);
    }
    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(250, 0));

        e->addComponent<RigidBody>();

        auto sprite = e->addComponent<Sprite>();

        sprite->setSpriteSheet(tiles);
        sprite->setCurrentFrame("tiles/0001");

        sprite->setSize(glm::vec2(100, 100));

        Scene::add(e);
    }

    {
        EntityHandle e = EntityFactory::create();

        auto transform = e->addComponent<Transform>();
        transform->setPosition(glm::vec2(350, 0));

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
