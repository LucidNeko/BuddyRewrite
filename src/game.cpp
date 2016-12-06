#include "game.h"

#include <string>

#include "systemopengl.h"

#include <QCoreApplication>
#include <QImage>
#include <QOpenGLTexture>
#include <QDebug>
#include <QLabel>

#include "entityfactory.h"
#include "entity.h"

#include "components/transform.h"
#include "components/rigidbody.h"
#include "components/sprite.h"
#include "logging.h"
#include "resources/io/resources.h"
#include "services.h"
#include "scenes/testscene.h"
#include "subsystems/physicssystem.h"
#include "subsystems/spriterenderer.h"
#include "resources/texture.h"
#include "input.h"

Game::Game()
    : _physicsSystem(nullptr),
      _spriteRenderer(nullptr)
{
}

Game::~Game()
{
    if(_currentScene)
    {
        _currentScene->onExit();
    }

    delete _physicsSystem;
    delete _spriteRenderer;

    LOG_INFO("Game destructor unloading unused resources");
    Services::get<Resources>()->unloadFreeResources();
}

bool Game::initialize()
{
    if (!gladLoadGL()) {
        LOG_FATAL("Failed to initialize OpenGL context");
        return false;
    }

    glClearColor(0.0, 0.0, 0.0, 1.0);

    _physicsSystem = new PhysicsSystem();
    _spriteRenderer = new SpriteRenderer();

    queueScene(std::make_shared<TestScene>());
    _processNextScene();

    return true;
}

void Game::tick()
{
    Time time(16666667);

    _processSubSystems(time);
    _processNextScene();

    Services::get<Input>()->update();
}

void Game::resize(I32 width, I32 height)
{
    LOG_INFO("%d, %d", width, height);
    glViewport(0, 0, width, height);
}

void Game::queueScene(SceneHandle scene)
{
    _nextScene = scene;
}

void Game::_processSubSystems(Time time)
{
    std::vector<EntityHandle> entities = _currentScene->getAll();

    _physicsSystem->update(time, entities);

    _spriteRenderer->render(entities);
    _spriteRenderer->flush();
}

void Game::_processNextScene()
{
    if(Services::get<Input>()->isKeyDownOnce(Qt::Key_N))
    {
        queueScene(std::make_shared<TestScene>());
    }

    if(!_nextScene) { return; }

    if(_currentScene)
    {
        _currentScene->onExit();
    }

    _currentScene = _nextScene;
    _nextScene.reset();

    if(_currentScene)
    {
        _currentScene->onEnter();
    }

    LOG_INFO("Unloadind unused resources");
    Services::get<Resources>()->unloadFreeResources();
}
