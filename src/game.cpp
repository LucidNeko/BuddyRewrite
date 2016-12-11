#include "game.h"

#include "systemopengl.h"

#include "assets/assets.h"
#include "assets/shaderprogram.h"
#include "assets/entity.h"
#include "subsystems/physicssystem.h"
#include "subsystems/animationsystem.h"
#include "subsystems/spriterenderer.h"

#include "logging.h"

#include "assets/scene.h"
#include "services.h"
#include "input.h"

Game::Game()
    : _assets(nullptr),
      _physicsSystem(nullptr),
      _animationSystem(nullptr),
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
    delete _animationSystem;
    delete _spriteRenderer;
}

bool Game::initialize()
{
    if (!gladLoadGL()) {
        LOG_FATAL("Failed to initialize OpenGL context");
        return false;
    }

    _assets = std::make_shared<Assets>();

    glClearColor(0.0, 0.0, 0.0, 1.0);

    _physicsSystem = new PhysicsSystem();
    _animationSystem = new AnimationSystem();
    _spriteRenderer = new SpriteRenderer(_assets->get<ShaderProgram>("shaders/sprite"));

    queueScene(_assets->get<Scene>("scenes/test_scene"));
    _processNextScene();

    return true;
}

void Game::tick()
{
    GameTime time(16666667);

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

void Game::_processSubSystems(GameTime time)
{
    std::vector<EntityHandle> entities = _currentScene->getAll();

    _physicsSystem->update(time, entities);

    _animationSystem->update(time, entities);

    _spriteRenderer->render(entities);
    _spriteRenderer->flush();
}

void Game::_processNextScene()
{
    if(Services::get<Input>()->isKeyDownOnce(Qt::Key_N))
    {
        queueScene(_assets->get<Scene>("scenes/test_scene"));
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

    LOG_INFO("Free Unreferenced Resources");
    _assets->freeUnreferencedResources();
}
