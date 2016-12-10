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
    _assets->load<SpriteSheet>("images/characters");
    _assets->load<SpriteSheet>("images/tiles");

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

    Scene::add(Entity::load("entities/player", _assets.get()));
    Scene::add(Entity::load("entities/sign_left", _assets.get()));
    Scene::add(Entity::load("entities/sign_right", _assets.get()));
    Scene::add(Entity::load("entities/enemy", _assets.get()));
}

void TestScene::onExit()
{
    Scene::removeAll();
}
